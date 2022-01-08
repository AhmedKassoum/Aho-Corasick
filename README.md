# Compilation

make

# Suppression des fichiers générés

make clean

# Lancement du programme

bash script.sh # ou bien

./script # Si vous avez un Permission denied ---> (sudo chmod u+x script.sh)

<h1>Exécution sequentiel du programme sans le script</h1>

<h2>pour générer pseudo-aléatoirement des textes de longueur 50 000 sur des alphabets de taille 3</h2>
./genere-texte 50000 3 > texte3.txt 
<h2>pour générer pseudo-aléatoirement 3 ensembles de 10 mots de longueur entre 5 et 15</h2>
./genere-mots 10 5 25 3 > mots3.txt 
<h2>Recherche Aho-corasick avec la matrice de transition</h2>
./ac-matrice mots3.txt texte3.txt > res-ac-matrice
<h2>Recherche Aho-corasick avec la table de hachage</h2>
./ac-hachage mots3.txt texte3.txt > res-ac-hachage
