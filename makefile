########################

# Les fichiers qui contiennent les définitions publiques de notre
# liste doublement chaînée sont intlist.h et intnode.h. Ce sont les
# deux header files. Les utilisateurs de notre liste les incluront
# dans leur propres fichiers de code.

# Les fichiers qui contiennent les implémentations de notre liste sont
# intlist.cpp intnode.cpp.

# Le fichier main.cpp est un exemple de création d'un exécutable à
# partir de la liste i.e. il contient la définition de la fonction
# main

# Le Makefile
#############

# Nous définissons des variables pour indiquer les commandes que nous
# utilisons.

# le compilateur
CPP = g++

# le linker
LINK = $(CPP)
# Comme c'est, dans notre cas, la même commande que le compilateur, on
# l'initialise au contenu de la variable CPP qui est $(CPP)

# La commande pour la suppression (forcée) de fichiers
RM = rm -f

###
# Nous définissons des options pour les commandes

# l'option pour mettre vos fichiers en version de debug
DEBUG = -g

# les options de compilation
CPPFLAGS = -Wall
# -Wall permet d'avoir le plus de message possible (warning) de
# compilation, pour pinailler mettez aussi -pedantic

# les options de link
LDFLAGS = -lncurses

##########

# le nom de notre binaire
TARGET = rogue

# la liste des fichier d'implémentation (fichier sources) 
SRCS = boucle.cpp

# On calcule automatiquement la liste des fichiers objets (.o)
# correspondant à nos fichiers sources.
# Ce qui donnera ici OBJS = main.o intlist.o intnode.o
OBJS = $(subst .cpp,.o,$(SRCS))

# Règle de Makefile
###################
# Une règle du Makefile est constituée de "cible, dépendances, commandes"

# Si toutes les dépendances sont à jour, la cible est considérée à
# jour et aucune commande n'est exécutée.

# Si des dépendances ne sont pas à jour, elles sont mises à jour par
# l'exécution des commandes correspondant à leur propre cible, puis la
# cible courante est mise à jour par l'exécution des commandes.

# Attention les commandes commencent par une tabulation !

###
# On définit la cible principale de notre fichier makefile celle qui
# sera produite si vous tapez make sans argument. C'est simplement la
# première cible accessible de votre makefile !
all: $(TARGET)

###

# On indique les dépendances entre nos fichiers en fait ce sont déjà
# là des règles sous la forme "cible, dépendances, commandes" mais les
# commandes sont omises et seront données plus tard. En effet pour
# éviter de la redondance de code on indiquera comment de manière
# globale passer d'un .cpp à un .o sans le faire pour chacun des .cpp.

boucle.o: boucle.cpp RandomMapGenerator.h personnages_def.h personnages.h actions_rogue.h MapDisplay.h
# ou main.o: main.cpp intlist.h intnode.h ?
# voir la discussion dans intlist.h


# Pour considérer si une dépendance est à jour, make se fonde sur la
# date des dépendances (qui sont la plupart du temps des fichiers
# comme des .o, des binaires, etc.). Si l'un des fichiers dont votre
# cible dépend est plus récent que la cible alors la cible sera
# refaite ici si intlist.h ou main.cpp est plus récent que main.o alor
# celui-ci sera reproduit (par l'appel de la commande).

##########
# On définit la règle générique pour produire les .o à partir des .cpp
# (on aurait pu en mettre une par .cpp).

%.o: %.cpp
	$(CPP) $(CPPFLAGS) $(DEBUG) -c $<
# ATTENTION à la tabulation obligatoire en début de commande !

# Notez les options passées lors de la compilation DEBUG et CPPFLAGS.

###

# .PHONY sert à dire que all est une cible virtuelle, en effet on ne
# produira pas de fichier s'appelant all et donc on ne pourra a
# fortiori pas trouver la date du fichier all (on le lui dit par
# phony)
.PHONY : all

##########
# La production du binaire final i.e. on linke les .o avec les
# éventuelles libraries
$(TARGET): $(OBJS)
	$(LINK) -o $(TARGET) $(OBJS) $(LDFLAGS)

##########
# Par commodité on nettoie le répertoire courant des fichiers dérivés
# des sources. Là on supprime aussi l'exécutable ainsi que les
# fichiers des sauvegardes temporaires genre main.cpp~ (générés par
# certains éditeurs).
clean:
	$(RM) *.o $(TARGET) *~
