### ProjetoExperimental_2_2017
Repositório criado após a conclusão do projeto,  apenas para expor os códigos utilizados para
os cálculos das estatísticas.

Arquivos necessarios para servir de entrada:
+ USA-roda-d.NY.co
+ USA-road-d.NY.gr
+ input

### Como rodar os experimentos?
Tendo todos os arquivos acima no mesmo diretório
no qual se localiza o arquivo *experimentos.cpp*, 
rode, no diretório vigente, os comandos abaixo:

    ```
    g++ -std=c++14 experimentos.cpp -o experimentos
    ./experimentos < input_adjusted
    ```

+ Após a execução do programa, tem-se diversos novos
arquivos, quais sejam:
    + <?>_t
    + <?>_q
    + <?>_pushed
    + <?>_heuristicas
    
