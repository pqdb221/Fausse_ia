# Fausse IA

**Un chatbot local développé entièrement en C++.**

Fausse IA est un chatbot expérimental qui simule une intelligence artificielle sans utiliser d'API externe ni de modèle d'IA en ligne.

Tout fonctionne localement grâce au C++ et à une base de connaissances personnalisée.

## Fonctionnalités

* Chatbot local
* Base de connaissances
* Mémoire persistante
* Correction des fautes de frappe
* Reconnaissance des synonymes
* Apprentissage manuel
* Système d'XP
* Fonctionnement sans API
* Fonctionnement sans modèle d'IA externe
* Utilisation directement dans le terminal

## Comment ça fonctionne

Au lieu d'utiliser un réseau neuronal, Fausse IA combine plusieurs techniques :

* une base de connaissances locale ;
* la reconnaissance de mots-clés ;
* la recherche de synonymes ;
* la correction des fautes ;
* la sauvegarde des données ;
* l'ajout manuel de connaissances.

Le but est d'expérimenter et de voir jusqu'où on peut aller pour créer un comportement ressemblant à celui d'une IA avec des techniques classiques de programmation en C++.

## Installation

Clone le dépôt :

```bash
git clone https://github.com/pqdb221/Fausse_ia.git
cd Fausse_ia
```

Compile le programme :

```bash
make
```

Puis lance-le :

```bash
./fausse-ia
```

## Exemple

```text
> bonjour

Bonjour ! Comment vas-tu ?

> linux

Linux est un système d'exploitation...

> apprendre

Que veux-tu m'apprendre ?
```

## Pourquoi ce projet ?

Fausse IA est une expérience visant à créer un système ressemblant à une IA à partir de zéro, sans utiliser de service d'IA en ligne.

Le projet permet notamment d'expérimenter avec :

* le C++ ;
* les algorithmes ;
* le traitement du langage ;
* les bases de connaissances ;
* la mémoire ;
* les systèmes conversationnels.

## Feuille de route

* [ ] Améliorer la compréhension du langage naturel
* [ ] Améliorer la correction des fautes
* [ ] Améliorer le système de mémoire
* [ ] Ajouter un historique des conversations
* [ ] Ajouter plusieurs bases de connaissances
* [ ] Créer des versions pour Linux et Windows
* [ ] Ajouter un fichier de configuration
* [ ] Améliorer le système d'apprentissage

## Technologies

* C++
* Make
* Terminal
* Fichiers locaux

## Licence

Projet open source.
