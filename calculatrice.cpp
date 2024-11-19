#include <iostream>
#include <string>
#include <sstream>
#include <stack>
#include <cmath>
#include <cctype>

// opération binaire
double calculerOperation(double a, double b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return b != 0 ? a / b : NAN;
        case '^': return pow(a, b);
        default: return NAN;
    }
}

// calculer des fonctions scientifiques
double calculerFonction(const std::string& fonction, double valeur) {
    if (fonction == "sin") return sin(valeur);
    if (fonction == "cos") return cos(valeur);
    if (fonction == "tan") return tan(valeur);
    if (fonction == "log") return valeur > 0 ? log10(valeur) : NAN; // Vérifie la validité du log
    if (fonction == "ln") return valeur > 0 ? log(valeur) : NAN;    // Vérifie la validité du ln
    if (fonction == "exp") return exp(valeur);
    if (fonction == "sqrt") return valeur >= 0 ? sqrt(valeur) : NAN; // Vérifie la racine carrée
    return NAN;
}

// Fonction pour vérifier si une chaîne est un nombre
bool estNombre(const std::string& str) {
    std::istringstream iss(str);
    double val;
    return (iss >> val) && (iss.eof());
}
// Fonction pour analyser et évaluer une expression mathématique
double evaluerExpression(const std::string& expression) {
    std::istringstream stream(expression);
    std::stack<double> valeurs;
    std::stack<char> operateurs;
    std::stack<std::string> fonctions;

    std::string token;
    while (stream >> token) {
        if (estNombre(token)) {
            valeurs.push(std::stod(token));
        } else if (token == "+" || token == "-" || token == "*" || token == "/" || token == "^") {
            operateurs.push(token[0]);
        } else if (token == "(") {
            operateurs.push('(');
        } else if (token == ")") {
            // Résoudre l'expression dans les parenthèses
            while (!operateurs.empty() && operateurs.top() != '(') {
                if (valeurs.size() < 2) {
                    std::cerr << "Erreur : Expression mal formée !\n";
                    return NAN;
                }
                double b = valeurs.top(); valeurs.pop();
                double a = valeurs.top(); valeurs.pop();
                char op = operateurs.top(); operateurs.pop();
                valeurs.push(calculerOperation(a, b, op));
            }
            if (!operateurs.empty() && operateurs.top() == '(') {
                operateurs.pop();
            }
            if (!fonctions.empty()) {
                if (valeurs.empty()) {
                    std::cerr << "Erreur : Paramètre manquant pour la fonction !\n";
                    return NAN;
                }
                double val = valeurs.top(); valeurs.pop();
                valeurs.push(calculerFonction(fonctions.top(), val));
                fonctions.pop();
            }
        } else {
            fonctions.push(token); 
        }
    }

    while (!operateurs.empty()) {
        if (valeurs.size() < 2) {
            std::cerr << "Erreur : Expression mal formée !\n";
            return NAN;
        }
        double b = valeurs.top(); valeurs.pop();
        double a = valeurs.top(); valeurs.pop();
        char op = operateurs.top(); operateurs.pop();
        valeurs.push(calculerOperation(a, b, op));
    }

    return valeurs.empty() ? NAN : valeurs.top();
}

void calculatrice() {
    std::string entree;

    while (true) {
        std::cout << "Entrez une expression (ou 'exit' pour quitter) : ";
        std::getline(std::cin, entree);

        if (entree == "exit") {
            std::cout << "Au revoir !\n";
            break;
        }

        try {
            double resultat = evaluerExpression(entree);
            if (std::isnan(resultat)) {
                std::cout << "Erreur : Expression invalide ou division par zéro !\n";
            } else {
                std::cout << "Résultat : " << resultat << "\n";
            }} catch (...) {
            std::cout << "Erreur : Une exception s'est produite !\n";
        }
    }
}

int main() {
    std::cout << "====== Calculatrice Scientifique ======\n";
    std::cout << "Fonctions supportées : sin(x), cos(x), tan(x), log(x), ln(x), exp(x), sqrt(x)\n";
    std::cout << "Opérations : +, -, *, /, ^\n";
    std::cout << "Entrez 'exit' pour quitter.\n";
    std::cout << "========================================\n";

    calculatrice();
    return 0;
}
        