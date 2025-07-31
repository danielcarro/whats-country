#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <locale>
#include <limits>
#include <map>

using namespace std;

struct Pais {
    string nome;
    string continente;
    string idioma;
    string capital;
    string bandeira;  
};

void limparBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void exibirIntroducao() {
    cout << "🎯 Bem-vindo ao Jogo de Adivinhação de Países!" << endl;
    cout << "=============================================" << endl;
    cout << "Você receberá dicas sobre um país e deve adivinhar qual é." << endl;
    cout << "Quanto menos tentativas você usar, maior será sua pontuação!" << endl << endl;
}

void exibirDica(const string& dica) {
    cout << "\n🔍 Dica: " << dica << endl;
}

void exibirVitoria(int tentativas, const string& pais) {
    cout << "\n🎉 Parabéns! Você acertou que o país é " << pais << " em " << tentativas << " tentativa(s)!" << endl;
    
    map<int, string> premios = {
        {1, "🏆 Medalha de Ouro em Geografia!"},
        {2, "🏆 Medalha de Prata em Geografia!"},
        {3, "🏆 Medalha de Bronze em Geografia!"},
        {5, "🌟 Estrela de Geógrafo Novato!"}
    };
    
    auto premio = premios.lower_bound(tentativas);
    if (premio != premios.end()) {
        cout << premio->second << endl;
    }
}

void exibirDerrota(const string& pais) {
    cout << "\n😢 Você não conseguiu adivinhar. O país era: " << pais << endl;
    cout << "Não desista! Tente novamente para melhorar seu conhecimento geográfico." << endl;
}

bool verificarPalpite(const string& palpite, const string& resposta) {
    string palpiteLower = palpite;
    string respostaLower = resposta;
    
    transform(palpiteLower.begin(), palpiteLower.end(), palpiteLower.begin(), ::tolower);
    transform(respostaLower.begin(), respostaLower.end(), respostaLower.begin(), ::tolower);
    
    return palpiteLower == respostaLower;
}

void jogarNovamente();

void jogarJogo(const vector<Pais>& paises) {
    int indice = rand() % paises.size();
    Pais escolhido = paises[indice];

    vector<string> dicas = {
        "Continente: " + escolhido.continente,
        "Idioma(s) oficial(is): " + escolhido.idioma,
        "Descrição da bandeira: " + escolhido.bandeira,
        "Capital: " + escolhido.capital
    };

    string palpite;
    int tentativas = 0;
    bool acertou = false;

    cout << "\n=== Novo Jogo ===" << endl;

    for (size_t i = 0; i < dicas.size() && !acertou; i++) {
        exibirDica(dicas[i]);
        cout << "🌍 Qual é o país? ";
        getline(cin, palpite);

        tentativas++;

        if (verificarPalpite(palpite, escolhido.nome)) {
            exibirVitoria(tentativas, escolhido.nome);
            acertou = true;
        } else {
            cout << "❌ Incorreto. ";
            if (i < dicas.size() - 1) {
                cout << "Aqui está outra dica..." << endl;
            }
        }
    }

    if (!acertou) {
        exibirDerrota(escolhido.nome);
    }

    jogarNovamente();
}

void jogarNovamente() {
    cout << "\nDeseja jogar novamente? (s/n): ";
    char opcao;
    cin >> opcao;
    limparBuffer();

    if (tolower(opcao) == 's') {
        jogarJogo({
            {"Brasil", "América do Sul", "Português", "Brasília", "Verde com losango amarelo e círculo azul"},
            {"Japão", "Ásia", "Japonês", "Tóquio", "Branco com círculo vermelho no centro"},
            {"França", "Europa", "Francês", "Paris", "Tricolor vertical: azul, branco e vermelho"},
            {"Canadá", "América do Norte", "Inglês e Francês", "Ottawa", "Vermelha com folha de bordo no centro"},
            {"Egito", "África", "Árabe", "Cairo", "Vermelha, branca e preta com águia de Saladino"},
            {"Austrália", "Oceania", "Inglês", "Canberra", "Azul com Union Jack e estrelas brancas"},
            {"Índia", "Ásia", "Hindi e Inglês", "Nova Delhi", "Tricolor horizontal: açafrão, branco e verde com roda azul"},
            {"México", "América do Norte", "Espanhol", "Cidade do México", "Tricolor vertical: verde, branco e vermelho com brasão"},
            {"Itália", "Europa", "Italiano", "Roma", "Tricolor vertical: verde, branco e vermelho"},
            {"Argentina", "América do Sul", "Espanhol", "Buenos Aires", "Azul claro e branco com sol no centro"}
        });
    } else {
        cout << "\nObrigado por jogar! Até a próxima! 👋" << endl;
    }
}

int main() {
#ifdef _WIN32
    system("chcp 65001 > nul"); // Terminal Windows em UTF-8
#endif
    setlocale(LC_ALL, "pt_BR.UTF-8"); // Suporte a acentuação

    srand(time(0));

    exibirIntroducao();
    jogarJogo({
        {"Brasil", "América do Sul", "Português", "Brasília", "Verde com losango amarelo e círculo azul"},
        {"Japão", "Ásia", "Japonês", "Tóquio", "Branco com círculo vermelho no centro"},
        {"França", "Europa", "Francês", "Paris", "Tricolor vertical: azul, branco e vermelho"},
        {"Canadá", "América do Norte", "Inglês e Francês", "Ottawa", "Vermelha com folha de bordo no centro"},
        {"Egito", "África", "Árabe", "Cairo", "Vermelha, branca e preta com águia de Saladino"}
    });

    return 0;
}