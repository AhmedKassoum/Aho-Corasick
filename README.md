# Compilation

make

# Suppression des fichiers générés (executables et objets) ---> (Nettoyage)

make clean

# Lancement du programme

bash script.sh # ou bien

./script # Si vous avez un Permission denied ---> (sudo chmod u+x script.sh)

# Exécution sequentiel du programme sans le script

./genere-texte 50000 3 > texte3.txt # pour générer pseudo-aléatoirement des textes de longueur 50 000 sur des alphabets de taille 3
./genere-mots 10 5 25 3 > mots3.txt # pour générer pseudo-aléatoirement 3 ensembles de 10 mots de longueur entre 5 et 15,
./ac-matrice mots3.txt texte3.txt > res-ac-matrice # Recherche Aho-corasick avec la matrice de transition
./ac-hachage mots3.txt texte3.txt > res-ac-hachage # Recherche Aho-corasick avec la table de hachage
