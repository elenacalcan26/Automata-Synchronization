# Automata-Synchronization
  
  
  Este implementat un program ce primeste reprezentarea unui automat si geseste
  secventele de sincronizare   
  

### 1. Task1 - Accesible
-------------------------  


   • starile accesibile sunt determinate de o parcurgere BFS ce porneste din 
      toate starile initiale ale automatului  
      
   • starile accesibile reprezinta toate nodurile vizitate in timpul parcurgerii

  
  
### 2. Task2 - Productive
--------------------------  


   • s-a folosit un algoritm BFS pentru a determina starile productive  
   
   • o stare este productiva daca parcurgerea incepe din ea si se termina in
      una din starile finale

  
  
### 3. Task3 - Useful
-------------------------  


   • s-a facut o parcurgere BFS de la toate starile intialae pana la toate 
    starilevfinale la care putea ajunge  
    
   • starile utile ale automatului sunt reprezentate de nodurile care formeaza
      un drum de la nodul sursa la nodul destinatie

  
  
### 4. Task4 - Synchronize
-------------------------  


   • s-a folosit o parcurgere BFS care porneste din 2 stari diferite, luate
      din multimea X

            X = multimea de stari din care incep parcurgerea

   • o secventa de sincronizare este gasit atunci cand cele 2 noduri ajung
      in aceeasi stare, urmand aceleasi tranzitii  
      
   • cand s-a descoprit o secventa, pentru fiecare stare din X se fac 
      tranzitii pe secventa si se salveaza nodurile finale din urma
      tranzitiilor  
      
   • multimea X este decrementata, avand doar starile finale determinate 
      anteriror  

  • se actualizeaza cuvantul de sincronizare final  
  
   • se repeta pana cand multimea X are cel mult o stare  
   
