// pch.h : Il s'agit d'un fichier d'en-tête précompilé.
// Les fichiers listés ci-dessous sont compilés une seule fois, ce qui améliore les performances de génération des futures builds.
// Cela affecte également les performances d'IntelliSense, notamment la complétion du code et de nombreuses fonctionnalités de navigation du code.
// Toutefois, les fichiers listés ici sont TOUS recompilés si l'un d'entre eux est mis à jour entre les builds.
// N'ajoutez pas de fichiers fréquemment mis à jour ici, car cela annule les gains de performance.

#ifndef PCH_H
#define PCH_H

// ajouter les en-têtes à précompiler ici
#include <RetroCode.h>
#include <Windows.h>

#ifdef _DEBUG
#define BEGIN_MEMORY_CHECK \
	_CrtMemState s1;\
	_CrtMemState s2;\
	_CrtMemState s3;\
	_CrtMemCheckpoint(&s1);\
	{\

#define END_MEMORY_CHECK \
	}\
	_CrtMemCheckpoint(&s2);\
	Assert::IsFalse(_CrtMemDifference(&s3, &s1, &s2));\

#else
#define BEGIN_MEMORY_CHECK
#define END_MEMORY_CHECK
#endif

#endif //PCH_H
