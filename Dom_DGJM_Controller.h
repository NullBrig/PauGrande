
void jogo(); //Responsavel pelo loop do jogo
void embaralharPecas(); //Embaralha a ordem das pecas
void distribuirPecas(); //Atribui as pecas para os jogadores e para o deposito de compra
void primeiroLance(); //Descobre e carrega a primeira peça na mesa
void comprarPeca(); //Compra uma peca caso possivel
void turnos(); //Atualiza os turnos
void passar(); //Passa a vez do jogador
void verificarPecasJogador(); //Verifica se o jogador da vez tem pecas que possam ser jogadas
void jogarE(); //"Empurra" as pecas para o lado direito
void jogarPeca(); //Joga a peca na mesa
void contarPecasMesa(); //Verifica a quantidade de pecas na mesa
int fim(); // Verifica as condições para o fim do jogo e determina o vencedo
void gravaCadastro(); // Salva o Jogo
void fRecuperaCadastro(); //Carrega jogo salvo
int jogarCPU();
void ftempo(int seg);