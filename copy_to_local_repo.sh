#Pega o que está no master e traz.
cd  "/cygdrive/c/Users/luciano/Documents/programacao/real_time_volume_rendering_repo" 
git checkout master
git pull #to update the state of the remote master branch
#
#Faz a sincronia com o diretório do repositório
cd  "/cygdrive/c/Users/luciano/Documents/programacao/real_time_volume_rendering" 
rsync -avm --include='*.cpp' --include='*.rtf' --include='*.cd' --include='*.h' --include='CMakeLists.txt' --include='*.png' --include='*.sh' --include='*.shader' -f 'hide,! */' . "/cygdrive/c/Users/luciano/Documents/programacao/real_time_volume_rendering_repo"

#Adiciona, commita e pusha
cd  "/cygdrive/c/Users/luciano/Documents/programacao/real_time_volume_rendering_repo" 
git add .;
git status;
git commit --message="$1";
git push --repo=https://luciano-geronimo:abc,123@github.com/luciano-geronimo/estudos_volume_rendering.git;



#git push --repo=https://dongeronimo:abc,123@github.com/dongeronimo/my_volume_rendering.git;