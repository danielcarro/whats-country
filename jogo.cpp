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

void limparBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void exibirIntroducao() {
    cout << "🎯 Bem-vindo ao Jogo de Adivinhacao de Paises!\n";
    cout << "=============================================\n";
    cout << "Voce recebera dicas sobre um pais e deve adivinhar qual e.\n";
    cout << "Quanto menos tentativas voce usar, maior sera sua pontuacao!\n\n";
}

void exibirDica(const string& dica) {
    cout << "\n🔍 Dica: " << dica << "\n";
}

void exibirVitoria(int tentativas, const string& pais) {
    cout << "\n🎉 Parabens! Voce acertou que o pais e " << pais << " em " << tentativas << " tentativa(s)!\n";

    map<int, string> premios = {
        {1, "🏆 Medalha de Ouro em Geografia!"},
        {2, "🥈 Medalha de Prata em Geografia!"},
        {3, "🥉 Medalha de Bronze em Geografia!"},
        {5, "🌟 Estrela de Geografo Novato!"}
    };

    auto it = premios.lower_bound(tentativas);
    if (it != premios.end()) {
        cout << it->second << "\n";
    }
}

void exibirDerrota(const string& pais) {
    cout << "\n😢 Voce nao conseguiu adivinhar. O pais era: " << pais << "\n";
    cout << "Nao desista! Tente novamente para melhorar seu conhecimento geografico.\n";
}

bool verificarPalpite(const string& palpite, const string& resposta) {
    string p = palpite, r = resposta;
    transform(p.begin(), p.end(), p.begin(), ::tolower);
    transform(r.begin(), r.end(), r.begin(), ::tolower);
    return p == r;
}

bool jogarRodada(const Pais& pais) {
    vector<string> dicas = {
        "Continente: " + pais.continente,
        "Idioma(s) oficial(is): " + pais.idioma,
        "Descricao da bandeira: " + pais.bandeira,
        "Capital: " + pais.capital
    };

    string palpite;
    int tentativas = 0;

    for (const auto& dica : dicas) {
        exibirDica(dica);
        cout << "🌍 Qual e o pais? ";
        getline(cin, palpite);
        tentativas++;

        if (verificarPalpite(palpite, pais.nome)) {
            exibirVitoria(tentativas, pais.nome);
            return true;
        } else {
            cout << "❌ Incorreto.";
            if (tentativas < dicas.size()) cout << " Vamos tentar outra dica...\n";
        }
    }

    exibirDerrota(pais.nome);
    return false;
}

bool desejaContinuar() {
    cout << "\nDeseja jogar novamente? (s/n): ";
    char resposta;
    cin >> resposta;
    limparBuffer();
    return tolower(resposta) == 's';
}

void iniciarJogo(const vector<Pais>& paises) {
    bool jogando = true;
    while (jogando) {
        cout << "\n=== NOVA RODADA ===\n";
        Pais paisAleatorio = paises[rand() % paises.size()];
        jogarRodada(paisAleatorio);
        jogando = desejaContinuar();
    }

    cout << "\nObrigado por jogar! Ate a proxima! 👋\n";
}

int main() {
#ifdef _WIN32
    system("chcp 65001 > nul"); // Forca UTF-8 no terminal do Windows
#endif
    setlocale(LC_ALL, "pt_BR.UTF-8");
    srand(static_cast<unsigned>(time(0)));

    exibirIntroducao();
    vector<Pais> paises = carregarPaises();
    iniciarJogo(paises);

    return 0;
}