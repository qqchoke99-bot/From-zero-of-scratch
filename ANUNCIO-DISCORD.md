# Anúncio para Discord — CameraOverhaul v1.1.0-beta

Copie o bloco abaixo e cole direto no Discord. A formatação já está pronta.

---

# 🎥 CameraOverhaul — v1.1.0-beta

### Câmera cinematográfica para Minecraft Bedrock

> Sua câmera para de ser um bloco de gelo. Ela **inclina** quando você acelera, **rola** quando você faz a curva e **respira** quando você fica parado.

**Autor:** `DrukisMC`
**Plataforma:** Minecraft Bedrock (Android · arm64)
**Loader:** LeviLauncher
**Licença:** GPL-3.0

## 📥 Download

**[⬇️ BAIXAR — CameraOverhaul.levipack](https://www.mediafire.com/file/tya11c4gnalecrm/CameraOverhaul.levipack/file)**

Código-fonte: <https://github.com/DrukisMC/CameraOverhaul>

## ⚠️ AVISO IMPORTANTE — LEIA ANTES

> ### 🤢 Este mod pode causar enjoo, náusea ou tontura
>
> Ele mexe **diretamente** com o movimento da câmera. Isso pode desencadear **enjoo de movimento** (*motion sickness*), náusea, tontura, dor de cabeça, cansaço visual ou desorientação — **mesmo em quem nunca sentiu isso antes**.
>
> **Não use se você:**
> ⁃ é sensível a enjoo de movimento, cinetose ou enjoo de viagem
> ⁃ tem enxaqueca, vertigem, labirintite ou distúrbio vestibular
> ⁃ tem epilepsia fotossensível ou histórico de convulsões
> ⁃ está grávida, indisposto, com sono ou sob efeito de álcool
>
> **Se sentir qualquer desconforto, PARE na hora.** Não tente "se acostumar" — isso costuma piorar. Sintomas podem persistir por um tempo depois de fechar o jogo.

### ✅ Como usar com segurança

**Comece pelo preset de conforto**, não pelo padrão:

```
Overall Smoothness ......... 2.0
Forward Pitch Intensity .... 0.4
Vertical Pitch Intensity ... 0.3
Turning Roll Intensity ..... 0.4
Strafing Roll Intensity .... 0.4
Sway Intensity ............. 0.5
```

⁃ Jogue **10–15 minutos** e veja como se sente
⁃ Só aumente se estiver 100% confortável, **de 0.2 em 0.2**
⁃ Faça pausas a cada 30 minutos
⁃ Jogue em ambiente bem iluminado, com o celular mais longe do rosto

**Todo efeito pode ser desligado.** Coloque qualquer intensidade em `0`, ou use os toggles **Pitch**, **Roll** e **Idle Sway** para desativar grupos inteiros. Se desligar os três, o mod fica 100% inerte.

## ✨ O que ele faz

**🏃 Pitch de movimento**
A câmera inclina pra frente quando você acelera e levanta quando você cai — proporcional à velocidade real.
`~2,5° correndo` · `~13,5° em mergulho de elytra` · `~6° em queda terminal`

**🎢 Roll de curva**
Virar a câmera inclina ela pra dentro da curva, como um piloto fazendo uma volta. Andar de lado (strafe) tem seu próprio roll.
`~11° de pico nas curvas fortes`

**🌬️ Sway de descanso**
Fique parado e a câmera passa a flutuar de leve, como quem respira. Some no instante em que você se move.

## ⚙️ Configuração

**17 controles** no menu do LeviLauncher, organizados em 3 grupos. Desligar um grupo esconde os controles dele.

| Grupo | Controles |
|---|---|
| **Pitch** | Intensidade e suavização (frente + vertical) |
| **Roll** | Intensidade, acúmulo, suavização, strafe |
| **Idle Sway** | Intensidade, frequência, delay e tempos de fade |

**🎚️ Overall Smoothness** ajusta o "peso" da câmera inteira de uma vez.
`Mais alto` = pesada e cinematográfica · `Mais baixo` = seca e responsiva

**Presets sugeridos:**
```
😌 Conforto     Smoothness 2.0 · Pitch 0.4 · Roll 0.4
⚖️ Padrão       tudo em 1.0
🎬 Cinematográfico  Smoothness 1.5 · Pitch 1.5 · Roll 1.4
```

## 🛡️ É seguro para servidores?

**Sim.** O mod **nunca** altera a rotação real do seu personagem — só o transform visual da câmera. Nenhum pacote de movimento é modificado, nada é enviado ao servidor. É puramente visual, do seu lado.

Não dá vantagem nenhuma: é QoL/estético, não cheat.

## 🔧 Por baixo do capô

A lógica do jogo roda a **20 Hz**, mas a tela desenha a **60–144 Hz**. Na primeira versão a câmera era calculada no tick, então o valor ficava travado por vários frames e depois pulava — dava aquela sensação de engasgo.

Agora o tick só define o **alvo**, e uma **mola criticamente amortecida** persegue esse alvo **a cada frame renderizado**.

Resultado medido (tick 20 Hz, render 120 fps):
```
antes ...... 2,2743° de salto por frame
agora ...... 0,2916° de salto por frame   ⟶  87% menor
overshoot .. 0,000°
```

A mola usa a solução matemática exata em vez de aproximação por passos, então **não estoura nem oscila** se o FPS cair. Testado a 144 fps, 30 fps, FPS caótico de 12 a 144 e com travada de meio segundo — estável em todos.

A rotação é aplicada por **multiplicação de quaternion**, sem converter para ângulos de Euler. Isso evita *gimbal lock* quando você olha reto pra cima ou pra baixo.

## 💡 Créditos

Inspirado no mod **[CameraOverhaul](https://www.curseforge.com/minecraft/mc-mods/cameraoverhaul)** de **Mirsario & Contributors**, do Minecraft Java.

Esta é uma **reimplementação independente para Bedrock** — nenhum código foi copiado. Ambos os projetos são GPL-3.0.

## 🐛 Beta

Testado por build, simulação numérica e análise estática, mas **ainda com pouco tempo de jogo real**. Se achar bug ou algo estranho, comenta aqui ou abre uma issue no GitHub.

**Ainda não incluído:** tremores de tela (explosões, raios). A fila nativa do jogo só aguenta 2 entradas e o efeito precisa de 64, então vai precisar de implementação própria. Fica pra próxima versão.
