#include <iostream>
#include <dlfcn.h>
#include <stdio.h>
#include <string>


static int operation(int a, int b, std::string composant)
{
        int (*func)(int,int);
        int t = 0;
        void *handle;
        
        // Ouverture de la librairie
        if(composant.compare("Composant2")==0)
                handle = dlopen("./libComposant2.so", RTLD_LAZY);
        else
                handle = dlopen("./libComposant1.so", RTLD_LAZY);
        if(handle == NULL)
        {
                printf("erreur dlopen : %s\n", dlerror());
                exit(EXIT_FAILURE);
        }

        // Chargement de la fonction "func"
        if(composant.compare("Composant2") == 0)
        {
                *(void **) (&func) = dlsym(handle, "composant2");
                if (func == NULL)
                {
                        printf("Erreur dlsym : %s\n", dlerror());
                        dlclose(handle);
                        exit(EXIT_FAILURE);
                }

                // Exécution de la fonction "func"
                t = func(a,b);
        }
        else
        {
              *(void **) (&func) = dlsym(handle, "composant1");
                if (func == NULL)
                {
                        printf("Erreur dlsym : %s\n", dlerror());
                        dlclose(handle);
                        exit(EXIT_FAILURE);
                }

                // Exécution de la fonction "func"
                t = func(a,b);  
                std::cout << std::endl << " Valeur de retour :  " << t << std::endl;
        }
        // Fermeture de la librairie
        dlclose(handle);

        return t;
}

int main(int argc, char ** argv)
{
    if(argc != 4) exit(EXIT_FAILURE);
    
	int data1 = std::stoi(argv[2]);
	int data2 = std::stoi(argv[3]);

	int valeur=0;
        std::cout << argc << " " << argv[1];
        if(argc == 4)
        {
		std::string arg1(argv[1]);
                valeur = operation(data1, data2, arg1);
        }

        std::cout << std::endl;
	std::cout << "Valeur :" << valeur << std::endl;
}
