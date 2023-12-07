#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_set>

void read_file(const std::string& filename) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Erro ao abrir o arquivo: " << filename << std::endl;
        return;
    }

    std::string linha;

    while (std::getline(file, linha)) {
        std::vector<std::string> palavras;  // Array de palavras
        std::stringstream ss(linha);
        std::string palavra;

        while (std::getline(ss, palavra, ';')) {
            palavras.push_back(palavra);
        }

        // Agora, palavras contém o array de palavras da linha, separadas por ';'

        // Exemplo: exibindo as palavras
        std::cout << "Palavras na linha:" << std::endl;
        for (const auto& p : palavras) {
            std::cout << p << " palavra";
        }
        std::cout << std::endl;
    }

    file.close();
}



std::string format_data(const std::string& username, const std::unordered_set<int>& followers, int id) {
    std::ostringstream formatted_data;

    // Adiciona o username
    formatted_data << username << ";";

    // Adiciona os seguidores separados por ","
    for (auto it = followers.begin(); it != followers.end(); ++it) {
        formatted_data << *it;
        if (std::next(it) != followers.end()) {
            formatted_data << ",";
        }
    }

    // Adiciona o ID
    formatted_data << ";" << id;

    return formatted_data.str();
}

int main() {
    // Exemplo de uso da função read_file
    //read_file("database.txt");  // Substitua "arquivo.txt" pelo nome do seu arquivo


    // Exemplo de uso da função format_data
    std::string username = "usuario1";
    std::unordered_set<int> followers = {1, 2, 3, 4, 5, 6};
    int id = 15;  // Substitua pelo valor real do ID

    std::string formatted_string = format_data(username, followers, id);

    // Exibe o resultado formatado
    std::cout << "Formato da string: " << formatted_string << std::endl;
    
    return 0;
}
