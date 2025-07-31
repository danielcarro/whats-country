#include <iostream>                // Biblioteca para entrada e saída padrão (cin, cout)
#include <vector>                  // Permite o uso da estrutura de dados vetor (std::vector)
#include <cstdlib>                 // Funções utilitárias como rand, srand
#include <ctime>                   // Permite usar a função time para gerar aleatoriedade
#include <algorithm>              // Funções como transform para manipular strings
#include <locale>                  // Usado para definir a localização/idioma
#include <limits>                  // Para obter limites de tipos de dados (ex: streamsize)
#include <map>                     // Estrutura de dados mapa (chave-valor)

using namespace std;              // Permite o uso direto dos elementos do namespace std

// Estrutura para armazenar informações de um país
struct Pais {
    string nome;
    string continente;
    string idioma;
    string capital;
    string bandeira;  
};

// Função que retorna uma lista de países pré-definidos
vector<Pais> carregarPaises() {
    return {
        {"Brasil", "America do Sul", "Portugues", "Brasilia", "Verde com losango amarelo e circulo azul"},
        {"Japao", "Asia", "Japones", "Toquio", "Branco com circulo vermelho no centro"},
        {"Franca", "Europa", "Frances", "Paris", "Tricolor vertical: azul, branco e vermelho"},
        {"Canada", "America do Norte", "Ingles e Frances", "Ottawa", "Vermelha com folha de bordo no centro"},
        {"Egito", "Africa", "Arabe", "Cairo", "Vermelha, branca e preta com aguia de Saladino"},
        {"Australia", "Oceania", "Ingles", "Canberra", "Azul com Union Jack e estrelas brancas"},
        {"India", "Asia", "Hindi e Ingles", "Nova Delhi", "Tricolor horizontal: acafrao, branco e verde com roda azul"},
        {"Mexico", "America do Norte", "Espanhol", "Cidade do Mexico", "Tricolor vertical: verde, branco e vermelho com brasao"},
        {"Italia", "Europa", "Italiano", "Roma", "Tricolor vertical: verde, branco e vermelho"},
        {"Argentina", "America do Sul", "Espanhol", "Buenos Aires", "Azul claro e branco com sol no centro"}
    };
}

// Função que limpa o buffer do teclado após uma entrada com erro
void limparBuffer() {
    cin.clear(); // Limpa o estado de erro do cin
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignora até o fim da linha
}

// Exibe a introdução do jogo no console
void exibirIntroducao() {
    cout << "🎯 Bem-vindo ao Jogo de Adivinhacao de Paises!\n";
    cout << "=============================================\n";
    cout << "Voce recebera dicas sobre um pais e deve adivinhar qual e.\n";
    cout << "Quanto menos tentativas voce usar, maior sera sua pontuacao!\n\n";
}

// Exibe uma dica sobre o país
void exibirDica(const string& dica) {
    cout << "\n🔍 Dica: " << dica << "\n";
}

// Exibe mensagem de vitória e premiação conforme o número de tentativas
void exibirVitoria(int tentativas, const string& pais) {
    cout << "\n🎉 Parabens! Voce acertou que o pais e " << pais << " em " << tentativas << " tentativa(s)!\n";

    // Mapa de tentativas para prêmios
    map<int, string> premios = {
        {1, "🏆 Medalha de Ouro em Geografia!"},
        {2, "🥈 Medalha de Prata em Geografia!"},
        {3, "🥉 Medalha de Bronze em Geografia!"},
        {5, "🌟 Estrela de Geografo Novato!"}
    };

    // Encontra o prêmio apropriado com base no número de tentativas
    auto it = premios.lower_bound(tentativas);
    if (it != premios.end()) {
        cout << it->second << "\n"; // Exibe o prêmio
    }
}

// Exibe mensagem de derrota com o nome correto do país
void exibirDerrota(const string& pais) {
    cout << "\n😢 Voce nao conseguiu adivinhar. O pais era: " << pais << "\n";
    cout << "Nao desista! Tente novamente para melhorar seu conhecimento geografico.\n";
}

// Verifica se o palpite do jogador corresponde ao nome do país (sem diferenciar maiúsculas e minúsculas)
bool verificarPalpite(const string& palpite, const string& resposta) {
    string p = palpite, r = resposta;
    transform(p.begin(), p.end(), p.begin(), ::tolower); // Converte palpite para minúsculas
    transform(r.begin(), r.end(), r.begin(), ::tolower); // Converte resposta para minúsculas
    return p == r; // Compara os dois
}

// Função principal que executa uma rodada do jogo com um país sorteado
bool jogarRodada(const Pais& pais) {
    // Vetor com as dicas que serão dadas
    vector<string> dicas = {
        "Continente: " + pais.continente,
        "Idioma(s) oficial(is): " + pais.idioma,
        "Descricao da bandeira: " + pais.bandeira,
        "Capital: " + pais.capital
    };

    string palpite;
    int tentativas = 0;

    // Loop pelas dicas disponíveis
    for (const auto& dica : dicas) {
        exibirDica(dica);
        cout << "🌍 Qual e o pais? ";
        getline(cin, palpite); // Recebe o palpite do jogador
        tentativas++;

        if (verificarPalpite(palpite, pais.nome)) {
            exibirVitoria(tentativas, pais.nome); // Se acertar, mostra vitória
            return true;
        } else {
            cout << "❌ Incorreto.";
            if (tentativas < dicas.size()) cout << " Vamos tentar outra dica...\n";
        }
    }

    exibirDerrota(pais.nome); // Se errar todas, mostra derrota
    return false;
}

// Pergunta ao jogador se ele deseja continuar jogando
bool desejaContinuar() {
    cout << "\nDeseja jogar novamente? (s/n): ";
    char resposta;
    cin >> resposta; // Lê a resposta
    limparBuffer(); // Limpa o buffer do teclado
    return tolower(resposta) == 's'; // Retorna true se o jogador quiser continuar
}

// Função que gerencia o jogo completo
void iniciarJogo(const vector<Pais>& paises) {
    bool jogando = true;
    while (jogando) {
        cout << "\n=== NOVA RODADA ===\n";
        Pais paisAleatorio = paises[rand() % paises.size()]; // Sorteia um país aleatoriamente
        jogarRodada(paisAleatorio); // Executa a rodada com o país escolhido
        jogando = desejaContinuar(); // Pergunta se deseja continuar
    }

    cout << "\nObrigado por jogar! Ate a proxima! 👋\n";
}

// Função principal
int main() {
#ifdef _WIN32
    system("chcp 65001 > nul"); // Define codificação UTF-8 no terminal do Windows (para exibir acentos corretamente)
#endif
    setlocale(LC_ALL, "pt_BR.UTF-8"); // Define o local para português brasileiro
    srand(static_cast<unsigned>(time(0))); // Inicializa a semente para aleatoriedade

    exibirIntroducao(); // Exibe a introdução do jogo
    vector<Pais> paises = carregarPaises(); // Carrega a lista de países
    iniciarJogo(paises); // Começa o jogo

    return 0; // Fim do programa
}
