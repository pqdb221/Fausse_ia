# Fausse IA

**Un chatbot local expérimental développé entièrement en C++.**

Fausse IA est un programme qui simule certaines fonctionnalités d'une intelligence artificielle sans utiliser de modèle d'IA externe ni d'API.

Le programme fonctionne localement avec une base de connaissances, un système de recherche par mots-clés, une correction des fautes, des synonymes, une mémoire persistante et un système d'apprentissage.

## Fonctionnalités

### Chatbot

* Discussion dans le terminal
* Recherche dans une base de connaissances locale
* Recherche par mots-clés
* Reconnaissance de plusieurs synonymes
* Correction des fautes avec la distance de Levenshtein
* Mémoire simple du contexte
* Réponses aléatoires lorsque l'information est inconnue
* Possibilité d'apprendre une nouvelle réponse au programme

### Mémoire

Fausse IA sauvegarde certaines informations dans des fichiers locaux :

* Prénom de l'utilisateur
* XP
* Conversations
* Connaissances apprises

Les données sont conservées entre les lancements du programme.

### Système d'XP et de niveaux

Le programme possède un système d'expérience.

Les niveaux disponibles sont :

|      XP | Niveau        |
| ------: | ------------- |
|    0–99 | Débutant      |
| 100–249 | Intermédiaire |
| 250–499 | Programmeur   |
| 500–999 | Expert        |
|   1000+ | Hacker        |

À partir du niveau Hacker, le programme peut également lancer `cmatrix` sur Linux.

### Calculatrice

Une calculatrice simple est intégrée au programme.

Elle prend en charge :

* Addition
* Soustraction
* Multiplication
* Division
* Détection de la division par zéro

### Générateur de mots de passe

Le programme peut générer un mot de passe aléatoire de **16 caractères** composé de lettres majuscules, minuscules et chiffres.

### Discussion simple

Un mode de discussion séparé permet au programme de poser quelques questions à l'utilisateur et de répondre en fonction de ses choix.

## Comment fonctionne le chatbot ?

Le chatbot ne comprend pas réellement le langage comme un modèle d'intelligence artificielle moderne.

Il utilise plusieurs techniques classiques de programmation.

### 1. Normalisation

Les messages sont convertis en minuscules afin de faciliter les recherches.

### 2. Synonymes

Certains mots sont automatiquement remplacés par des termes équivalents.

Par exemple :

```text
ordinateur → pc
ordi       → pc
machine    → pc
portable   → pc
telephone  → smartphone
tel        → smartphone
```

### 3. Correction des fautes

Fausse IA utilise la **distance de Levenshtein** pour comparer les mots saisis avec ceux présents dans la base de connaissances.

Une différence suffisamment faible peut donc être corrigée automatiquement.

### 4. Recherche par mots-clés

La base de connaissances utilise le format :

```text
mot-cle=reponse
```

Le programme compare les mots de la question avec les sujets présents dans `connaissances.txt` et sélectionne la réponse correspondant au meilleur score.

### 5. Apprentissage

Lorsqu'une information est inconnue, le programme peut demander à l'utilisateur de lui apprendre la bonne réponse.

La nouvelle connaissance est alors ajoutée à la base de données.

Exemple :

```text
Toi : capitale france

IA : Je ne connais pas encore cette information.

Veux-tu m'apprendre la reponse ? (o/n) : o

Quelle est la bonne reponse ? Paris

IA : Merci, j'ai appris !
```

## Menu

Au lancement, Fausse IA propose :

```text
========== MENU ==========
1 - Parler avec l'IA
2 - Calculatrice
3 - Generer un mot de passe
4 - Voir niveau XP
5 - Apprendre une connaissance
6 - Discussion simple
0 - Quitter
==========================
```

## Installation

### Prérequis

Pour compiler le programme, il faut disposer d'un compilateur C++ et de `make`.

Sous Debian, Ubuntu ou KDE neon :

```bash
sudo apt install g++ make
```

### Télécharger le projet

```bash
git clone https://github.com/pqdb221/Fausse_ia.git
cd Fausse_ia
```

### Compiler

```bash
make
```

### Lancer

```bash
./fausse-ia
```

Le programme doit être lancé dans le même dossier que `connaissances.txt`.

## Fichiers générés

Pendant son fonctionnement, Fausse IA peut créer plusieurs fichiers permettant de conserver ses données :

```text
xp.txt
memoire.txt
conversation.txt
t.txt
```

Ces fichiers permettent notamment de conserver l'XP, le prénom et l'historique des conversations.

## Structure du projet

```text
Fausse_ia/
├── fausse-ia.cpp
├── fausse-ia
├── fausse_ia.exe
├── connaissances.txt
├── Makefile
└── README.md
```

## Technologies utilisées

* **C++**
* **Make**
* Terminal
* Fichiers texte
* Distance de Levenshtein
* Algorithmes de recherche par mots-clés

## Objectif du projet

Fausse IA est avant tout un projet d'expérimentation et d'apprentissage.

L'objectif est de créer progressivement un programme qui donne l'impression d'interagir avec une IA en utilisant uniquement du C++ et des algorithmes classiques.

Le projet permet notamment d'expérimenter avec :

* le traitement de texte ;
* les algorithmes ;
* la recherche de similarité ;
* la gestion de fichiers ;
* la mémoire persistante ;
* les systèmes conversationnels ;
* la programmation C++.

## Feuille de route

* [ ] Améliorer la compréhension du langage naturel
* [ ] Ajouter davantage de synonymes
* [ ] Améliorer la correction des fautes
* [ ] Améliorer la mémoire du contexte
* [ ] Améliorer le système d'apprentissage
* [ ] Améliorer le système de recherche dans la base de connaissances
* [ ] Ajouter davantage de commandes
* [ ] Améliorer le générateur de mots de passe
* [ ] Ajouter une meilleure interface dans le terminal
* [ ] Ajouter des versions compilées plus facilement disponibles

## Limites

Fausse IA **n'est pas un véritable modèle d'intelligence artificielle**.

Il ne s'agit pas d'un réseau neuronal et le programme ne génère pas ses réponses comme les modèles d'IA modernes.

Son fonctionnement repose principalement sur des règles, une base de connaissances, des mots-clés, des synonymes et des algorithmes de traitement de texte.

## Licence

Ce projet est distribué sous licence MIT.

Voir le fichier [LICENSE](LICENSE) pour le texte complet de la licence.
