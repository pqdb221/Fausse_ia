#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include <ctime>
#include <cstdlib>
#include <limits>

using namespace std;

// ============================================================
// VARIABLES GLOBALES
// ============================================================

string prenom;
string dernierSujet = "";
int xp = 0;

// ============================================================
// OUTILS
// ============================================================
bool lancerFauxRecaptcha() {
    string reponse;
    cout << "====================================================\n";
    cout << "🔒  reCAPTCHA DE SÉCURITÉ - LICENCE pqdb221  🔒\n";
    cout << "====================================================\n";
    cout << "[INFO] Pour verifier que vous n'etes pas un robot et que\n";
    cout << "       10 instances de Fausse_ia tournent en parallele,\n";
    cout << "       veuillez valider le test de securite.\n\n";
    cout << "👉 Tapez scrupuleusement la phrase suivante :\n";
    cout << "   \"Je jure que 10 instances de Fausse_ia tournent et que ma RAM va exploser\"\n\n";
    cout << "Votre reponse : ";
    
    getline(cin, reponse);
    cout << "\n[⚡] Verification de l'infrastructure memoire...\n";
    this_thread::sleep_for(chrono::seconds(2));
    
    if (reponse == "Je jure que 10 instances de Fausse_ia tournent et que ma RAM va exploser") {
        cout << "🟢 [SUCCESS] Humain detecte. Licence pqdb221 validee.\n\n";
        this_thread::sleep_for(chrono::seconds(1));
        return true;
    } else {
        cout << "\n❌ [ERREUR] Code incorrect.\n";
        cout << explosage de la ram a la place des fenêtres. \n;
        this_thread::sleep_for(chrono::seconds(3));
cout << "Tu as de la chance je suis gentil mais la prochaine fois c'est GitHub.\n";
    }
}

void viderEntree()
{
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

string minuscule(string texte)
{
    for (char &c : texte)
    {
        c = static_cast<char>(
            tolower(static_cast<unsigned char>(c))
        );
    }

    return texte;
}

// ============================================================
// MEMOIRE XP
// ============================================================

void chargerXP()
{
    ifstream fichier("xp.txt");

    if (fichier)
    {
        fichier >> xp;
    }
}

void sauvegarderXP()
{
    ofstream fichier("xp.txt");

    if (fichier)
    {
        fichier << xp;
    }
}
// ============================================================
// MEMOIRE PRENOM
// ============================================================

void chargerMemoire()
{
    ifstream fichier("memoire.txt");

    if (fichier)
    {
        getline(fichier, prenom);
    }
}

void sauverMemoire()
{
    ofstream fichier("memoire.txt");

    if (fichier)
    {
        fichier << prenom;
    }
}

// ============================================================
// SAUVEGARDE CONVERSATION
// ============================================================

void sauvegarder(const string &texte)
{
    ofstream fichier("conversation.txt", ios::app);

    if (fichier)
    {
        fichier << texte << endl;
    }
}

// ============================================================
// SYNONYMES
// ============================================================

string appliquerSynonymes(string texte)
{
    vector<pair<string, string>> synonymes =
    {
        {"ordinateur", "pc"},
        {"ordi", "pc"},
        {"machine", "pc"},
        {"portable", "pc"},
        {"telephone", "smartphone"},
        {"tel", "smartphone"}
    };

    for (const auto &s : synonymes)
    {
        size_t pos = texte.find(s.first);

        while (pos != string::npos)
        {
            texte.replace(pos, s.first.size(), s.second);
            pos = texte.find(s.first, pos + s.second.size());
        }
    }

    return texte;
}

// ============================================================
// DISTANCE DE LEVENSHTEIN
// ============================================================

int distanceLevenshtein(const string &a, const string &b)
{
    int n = static_cast<int>(a.size());
    int m = static_cast<int>(b.size());

    vector<vector<int>> d(
        n + 1,
        vector<int>(m + 1)
    );

    for (int i = 0; i <= n; i++)
    {
        d[i][0] = i;
    }

    for (int j = 0; j <= m; j++)
    {
        d[0][j] = j;
    }

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            int coutModification =
                (a[i - 1] == b[j - 1]) ? 0 : 1;

            d[i][j] = min({
                d[i - 1][j] + 1,
                d[i][j - 1] + 1,
                d[i - 1][j - 1] + coutModification
            });
        }
    }

    return d[n][m];
}

// ============================================================
// CORRECTION D'UN MOT
// ============================================================

string corrigerMot(const string &mot)
{
    if (mot.size() < 4)
    {
        return mot;
    }

    ifstream fichier("connaissances.txt");

    if (!fichier)
    {
        return mot;
    }

    string ligne;
    string meilleurMot = mot;
    int meilleureDistance = 999;

    while (getline(fichier, ligne))
    {
        size_t egal = ligne.find('=');

        if (egal == string::npos)
        {
            continue;
        }

        string connu = ligne.substr(0, egal);

        if (connu.size() < 4)
        {
            continue;
        }

        int distance = distanceLevenshtein(
            minuscule(mot),
            minuscule(connu)
        );

        if (distance < meilleureDistance)
        {
            meilleureDistance = distance;
            meilleurMot = connu;
        }
    }

    if (meilleureDistance <= 2)
    {
        return meilleurMot;
    }

    return mot;
}

// ============================================================
// RECHERCHE DANS LA BASE DE CONNAISSANCES
// ============================================================

string chercherConnaissance(string question)
{
    question = minuscule(question);
    question = appliquerSynonymes(question);

    vector<string> mots;
    string mot;

    for (char c : question)
    {
        if (isspace(static_cast<unsigned char>(c)))
        {
            if (!mot.empty())
            {
                mots.push_back(corrigerMot(mot));
                mot.clear();
            }
        }
        else
        {
            mot += c;
        }
    }

    if (!mot.empty())
    {
        mots.push_back(corrigerMot(mot));
    }

    ifstream fichier("connaissances.txt");

    if (!fichier)
    {
        return "";
    }

    string ligne;

    int meilleurScore = 0;
    string meilleureReponse = "";
    string meilleurSujet = "";

    while (getline(fichier, ligne))
    {
        size_t egal = ligne.find('=');

        if (egal == string::npos)
        {
            continue;
        }

        string sujet = ligne.substr(0, egal);
        string reponse = ligne.substr(egal + 1);

        sujet = minuscule(sujet);

        int score = 0;

        for (const string &m : mots)
        {
            if (!m.empty() && sujet.find(m) != string::npos)
            {
                score++;
            }
        }

        if (score > meilleurScore)
        {
            meilleurScore = score;
            meilleureReponse = reponse;
            meilleurSujet = sujet;
        }
    }

    if (meilleurScore > 0)
    {
        dernierSujet = meilleurSujet;
        return meilleureReponse;
    }

    // Mémoire simple du contexte
    if (!dernierSujet.empty())
    {
        if (question.find("il") != string::npos ||
            question.find("elle") != string::npos ||
            question.find("ça") != string::npos ||
            question.find("cela") != string::npos)
        {
            return chercherConnaissance(dernierSujet);
        }
    }

    return "";
}

// ============================================================
// APPRENDRE UNE CONNAISSANCE
// ============================================================

void apprendreConnaissance()
{
    string mot;
    string reponse;

    viderEntree();

    cout << "Mot cle : ";
    getline(cin, mot);

    cout << "Reponse : ";
    getline(cin, reponse);

    if (mot.empty() || reponse.empty())
    {
        cout << "IA : Information invalide." << endl;
        return;
    }

    ofstream fichier("connaissances.txt", ios::app);

    if (fichier)
    {
        fichier << minuscule(mot)
                << "="
                << reponse
                << endl;

        cout << "IA : Information enregistree !" << endl;

        xp += 10;
        sauvegarderXP();
    }
    else
    {
        cout << "IA : Erreur d'enregistrement." << endl;
    }
}

// ============================================================
// APPRENDRE UNE REPONSE APRES UNE QUESTION INCONNUE
// ============================================================

void apprendreReponse(const string &question)
{
    string reponse;

    cout << "Quelle est la bonne reponse ? ";
    getline(cin, reponse);

    if (reponse.empty())
    {
        cout << "IA : Reponse vide, rien n'a ete appris." << endl;
        return;
    }

    ofstream fichier("connaissances.txt", ios::app);

    if (fichier)
    {
        fichier << question
                << "="
                << reponse
                << endl;

        cout << "IA : Merci, j'ai appris !" << endl;
    }
    else
    {
        cout << "IA : Impossible d'enregistrer la connaissance." << endl;
    }
}

// ============================================================
// REPONSE ALEATOIRE
// ============================================================

void reponseAleatoire()
{
    vector<string> reponses =
    {
        "Je ne connais pas encore cette information.",
        "Je vais devoir apprendre cela.",
        "Information inconnue dans ma base.",
        "Je suis une IA qui n'est pas une IA."
    };

    size_t index =
        static_cast<size_t>(rand()) % reponses.size();

    cout << "IA : " << reponses[index] << endl;
}

// ============================================================
// CHATBOT
// ============================================================

void chatbot()
{
    string message;

    cout << "\n===== Discussion avec fausse IA =====" << endl;
    cout << "Tape 'quitter' pour revenir au menu." << endl;

    // Le menu utilise cin >> choix,
    // il faut donc supprimer le retour a la ligne.
    viderEntree();

    while (true)
    {
        cout << "\nToi : ";
        getline(cin, message);

        if (message.empty())
        {
            continue;
        }

        message = minuscule(message);

        if (message == "quitter")
        {
            cout << "IA : Retour au menu." << endl;
            break;
        }

        sauvegarder("Utilisateur : " + message);

        string reponse = chercherConnaissance(message);

        if (!reponse.empty())
        {
            cout << "IA : " << reponse << endl;
            sauvegarder("IA : " + reponse);
        }
        else
        {
            reponseAleatoire();

            cout << "Veux-tu m'apprendre la reponse ? (o/n) : ";

            string choix;
            getline(cin, choix);

            if (minuscule(choix) == "o" ||
                minuscule(choix) == "oui")
            {
                apprendreReponse(message);
            }
        }

        xp += 10;
        sauvegarderXP();
    }
}

// ============================================================
// NIVEAU
// ============================================================

void niveau()
{
    cout << "\nXP : " << xp << endl;

    if (xp < 100)
    {
        cout << "Niveau : Debutant" << endl;
    }
    else if (xp < 250)
    {
      cout << "Niveau : Intermédiaire"  << endl;
    }
    else if (xp < 500)
    {
        cout << "Niveau : Programmeur" << endl;
    }
    else if (xp < 1000)
    {
        cout << "Niveau : Expert" << endl;
    }
    else
    { int t = 0;
        ifstream fichier("t.txt");

    if (fichier)
    {
        fichier >> t;
    }
        cout << "Niveau : Hacker" <<endl;
        if (t == 0){
        system("cmatrix");
      ofstream fichier("t.txt");

    if (fichier)
    {
        fichier << "2";
    }
        }
        else { return ;}
    }
}
// ============================================================
// CALCULATRICE
// ============================================================

void calculatrice()
{
    double a;
    double b;
    char operation;

    cout << "Nombre 1 : ";

    if (!(cin >> a))
    {
        cout << "Erreur : nombre invalide." << endl;
        cin.clear();
        viderEntree();
        return;
    }

    cout << "Operation (+ - * /) : ";
    cin >> operation;

    cout << "Nombre 2 : ";

    if (!(cin >> b))
    {
        cout << "Erreur : nombre invalide." << endl;
        cin.clear();
        viderEntree();
        return;
    }

    if (operation == '+')
    {
        cout << "Resultat : " << a + b << endl;
    }
    else if (operation == '-')
    {
        cout << "Resultat : " << a - b << endl;
    }
    else if (operation == '*')
    {
        cout << "Resultat : " << a * b << endl;
    }
    else if (operation == '/')
    {
        if (b == 0)
        {
            cout << "Erreur : division par zero impossible." << endl;
        }
        else
        {
            cout << "Resultat : " << a / b << endl;
        }
    }
    else
    {
        cout << "Operation inconnue." << endl;
    }
}

// ============================================================
// GENERATEUR DE MOT DE PASSE
// ============================================================

void motDePasse()
{
    string caracteres =
        "abcdefghijklmnopqrstuvwxyz"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "0123456789";

    string mdp;

    for (int i = 0; i < 16; i++)
    {
        size_t index =
            static_cast<size_t>(rand()) % caracteres.size();

        mdp += caracteres[index];
    }

    cout << "Mot de passe genere : " << mdp << endl;
}

// ============================================================
// DISCUSSION SIMPLE
// ============================================================

void discussion()
{
    string nom;
    int age;

    cout << "\n===== Discussion simple =====" << endl;

    cout << "Bonjour, je suis Fausse IA." << endl;

    cout << "Pour commencer, donne-moi ton prenom : ";
    cin >> nom;

    cout << "Parfait " << nom
         << ", maintenant je dois connaitre ton age."
         << endl;

    cout << "Ecris ton age en chiffres : ";

    if (!(cin >> age))
    {
        cout << "Erreur : age invalide." << endl;
        cin.clear();
        viderEntree();
        return;
    }

    if (age < 10)
    {
        cout << "Desole " << nom
             << ", mais " << age
             << " ans ce n'est pas assez pour utiliser "
             << "cette discussion."
             << endl;

        cout << "Tu dois encore attendre "
             << 10 - age
             << " ans."
             << endl;

        return;
    }

    cout << "\nMaintenant que c'est bon, je vais te donner "
         << "une question et des reponses."
         << endl;

    cout << "Tu vas me repondre avec le chiffre de la reponse."
         << endl;

    cout << "\nQuestion : quel langage de programmation "
         << "utilises-tu couramment ?" << endl;

    cout << "1. Python" << endl;
    cout << "2. C++ / C" << endl;
    cout << "3. HTML" << endl;
    cout << "4. JavaScript / Java" << endl;
    cout << "5. Scratch" << endl;
    cout << "6. Autre" << endl;

    int language;

    cout << "Reponse : ";

    if (!(cin >> language))
    {
        cout << "Erreur : reponse invalide." << endl;
        cin.clear();
        viderEntree();
        return;
    }

    if (language == 1)
    {
        cout << "Python est un langage informatique "
             << "tres utilise car il est relativement "
             << "simple a apprendre."
             << endl;
    }
    else if (language == 2)
    {
        cout << "Le C et le C++ permettent un controle "
             << "important des ressources de la machine."
             << endl;

        cout << "Ils sont notamment utilises pour les "
             << "logiciels, les jeux, les systemes embarques "
             << "et de nombreux autres projets."
             << endl;
    }
    else if (language == 3)
    {
        cout << "HTML est un langage de balisage utilise "
             << "pour structurer les pages web."
             << endl;
    }
    else if (language == 4)
    {
        cout << "JavaScript est tres utilise pour rendre "
             << "les pages web interactives."
             << endl;

        cout << "Java est un langage different, utilise "
             << "notamment pour des applications."
             << endl;
    }
    else if (language == 5)
    {
        cout << "Scratch est un environnement de programmation "
             << "visuelle concu notamment pour apprendre "
             << "les bases de la programmation."
             << endl;
    }
    else if (language == 6)
    {
        cout << "Il existe beaucoup d'autres langages comme "
             << "Rust, Go, PHP, C#, Kotlin ou Swift."
             << endl;
    }
    else
    {
        cout << "Erreur : reponse invalide." << endl;
    }
}

// ============================================================
// PROGRAMME PRINCIPAL
// ============================================================

int main()
{       int main() {
    // Déclenchement du reCAPTCHA de pqdb221 au boot
    if (!lancerFauxRecaptcha()) {
        return 0; // Ferme proprement le programme sans crash
    }

  ofstream fichier("t.txt");

    if (fichier)
    {
        fichier << "0";
    }
    srand(static_cast<unsigned int>(time(nullptr)));

    chargerMemoire();
    chargerXP();

    cout << "==============================" << endl;
    cout << "        FAUSSE IA" << endl;
    cout << "==============================" << endl;

    if (prenom.empty())
    {
        cout << "Quel est ton prenom ? ";
        cin >> prenom;

        sauverMemoire();
    }

    cout << "Bienvenue " << prenom << " !" << endl;
    cout << "XP actuelle : " << xp << endl;

    int choix;

    while (true)
    {
        cout << "\n========== MENU ==========" << endl;
        cout << "1 - Parler avec l'IA" << endl;
        cout << "2 - Calculatrice" << endl;
        cout << "3 - Generer un mot de passe" << endl;
        cout << "4 - Voir niveau XP" << endl;
        cout << "5 - Apprendre une connaissance" << endl;
        cout << "6 - Discussion simple" << endl;
        cout << "0 - Quitter" << endl;
        cout << "==========================" << endl;

        cout << "Choix : ";

        if (!(cin >> choix))
        {
            cout << "Erreur : veuillez entrer un nombre." << endl;

            cin.clear();
            viderEntree();

            continue;
        }

        if (choix == 1)
        {
            chatbot();
        }
        else if (choix == 2)
        {
            calculatrice();
        }
        else if (choix == 3)
        {
            motDePasse();
        }
        else if (choix == 4)
        {
            niveau();
        }
        else if (choix == 5)
        {
            apprendreConnaissance();
        }
        else if (choix == 6)
        {
            discussion();
        }
        else if (choix == 0)
        {
            cout << "Au revoir " << prenom << " !" << endl;
            break;
        }
        else
        {
            cout << "Choix invalide." << endl;
        }
    }

    sauvegarderXP();
    sauverMemoire();

    return 0;
}
