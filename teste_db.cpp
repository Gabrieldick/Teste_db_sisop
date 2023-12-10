#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_set>
#include <iterator>

struct User{
		std::string username;
		int userId;
	};

class UserInfo {
		private:
			User user;
			int activeSessions;
			std::unordered_set<int> followers;

        public:
            int getId() const {
                return this->user.userId;
            }

            const std::string getUsername() const {
                return user.username;
            }

            const std::unordered_set<int> getFollowers() const {
                return this->followers;
            }


			UserInfo(int userId, std::string username, std::unordered_set<int> followers){
                this->user.username = username;
                this->user.userId = userId;
                this->followers = followers;
                this->activeSessions = 0;
            }
	};

// Função para converter uma string para um unordered_set de int
std::unordered_set<int> stringParaUnorderedSet(const std::string& input) {
    std::unordered_set<int> result;

    std::istringstream iss(input);
    int elemento;
    while (iss >> elemento) {
        result.insert(elemento);
        iss.ignore(1, ',');
    }

    return result;
}

// Função para converter um unordered_set de int para uma string
std::string unorderedSetParaString(const std::unordered_set<int>& mySet) {
    std::ostringstream oss;
    for (const auto& elemento : mySet) {
        oss << elemento << ",";
    }
    if (!mySet.empty()) {
        oss.seekp(-1, oss.cur);
    }
    return oss.str();
}

// Função para ler um arquivo e retornar um vetor de UserInfo
std::vector<UserInfo> read_file(const std::string& filename) {
    std::ifstream file(filename);
    std::vector<UserInfo> usuarios;

    if (!file.is_open()) {
        std::cerr << "Erro ao abrir o arquivo: " << filename << std::endl;
        return usuarios;  // Retorna vetor vazio em caso de erro
    }

    std::string linha;

    while (std::getline(file, linha)) {
        std::string username;
        std::string followers_str;
        int id;

        std::istringstream ss(linha);
        std::getline(ss, username, ';');
        std::getline(ss, followers_str, ';');
        ss >> id;

        std::unordered_set<int> followers = stringParaUnorderedSet(followers_str);

        // Criar UserInfo e adicionar ao vetor
        usuarios.push_back(UserInfo(id, username, followers));
    }

    file.close();

    return usuarios;
}

std::string format_data(const UserInfo& user) {
    std::ostringstream formatted_data;
    user.getFollowers();
    formatted_data << user.getUsername() << ";" << unorderedSetParaString(user.getFollowers()) << ";" << user.getId();
    return formatted_data.str();
}

// Função para escrever um vetor de UserInfo em um arquivo
void write_file(const std::string& filename, const std::vector<UserInfo>& users) {
    std::ofstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Erro ao abrir o arquivo para escrita: " << filename << std::endl;
        return;
    }

    for (const auto& user : users) {
        std::string formatted_data = format_data(user);
        file << formatted_data << std::endl;
    }

    file.close();
}

int main() {

    // Exemplo de uso da função read_file
    std::vector<UserInfo> usuarios = read_file("database.txt");

    // Exemplo de exibição dos dados lidos
    std::cout << "Dados lidos do arquivo:" << std::endl;
    for (const auto& users : usuarios) {
        std::cout << "Username: " << users.getUsername() << " - Seguidores: ";
        for (const auto& follower : users.getFollowers()) {
            std::cout << follower << ",";
        }
        std::cout << " - ID: " << users.getId() << std::endl;
    }


    return 0;
}
