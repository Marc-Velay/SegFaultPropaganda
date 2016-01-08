# SegFaultPropaganda
Projet X 2A ESIEA

hello!

git branch <nom de la branche> 		//créer une branche du nom <>
git checkout <nom de la branche>		//switch sur la branche <>

git commit -a -m '<commentaire du push>'	//commit (envoie le code) de la branche sur laquelle on est (le dernier checkout)

git checkout master					// switch sur la branche master
git merge hotfix					// assemble la branche <hotfix> et le dernier checkout

git push https://github.com/Marc-Velay/SegFaultPropaganda master //envoie sur le serveur
git pull https://github.com/Marc-Velay/SegFaultPropaganda master //récupère le code du serveur

pour mettre à jour:

git add .			//met tous le dossier en mode commit, pour être ajouté

git commit -m 'update tourelle.c et readme.txt'	//marque les nouveaux dossiers ayant besoin d'être push

git push https://github.com/Marc-Velay/SegFaultPropaganda master	//Envoie les fichiers marques à commit sur l'url 
