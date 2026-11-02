# satk — SIM Application Toolkit (Qt 6 Pilot)

Este é o piloto de reescrita do app `satk` (SIM Application Toolkit) do MeeGo/Harmattan, originalmente escrito em Qt 4 / QtDeclarative + C++ com D-Bus/oFono.

## Estrutura

```
satk-qt6/
├── CMakeLists.txt          # Build CMake (Qt 5.15 no momento, migrar para Qt 6)
├── main.cpp                # Entry point (menu/agent mode)
├── stkdefines.h            # Constantes e STK_AGENT_PATH
├── ofonodbustypes.h        # Interfaces D-Bus do oFono (Manager, Modem, Sim, Stk)
├── stkapplication.h/cpp    # Gerência de conexão oFono via D-Bus
├── stkmainwindow.h/cpp     # Janela principal com QQuickView
├── stkmenumodel.h/cpp      # Modelo de lista de menus (QML)
├── stkofonoproperties.h/cpp # Propriedades do menu principal do SIM
├── stkofonoutils.h/cpp     # Utilitários de descoberta de modems oFono
├── simimageprovider.h/cpp  # Provedor de imagens SIM para QML
├── stkagentservice.h/cpp   # Serviço D-Bus org.ofono.SimToolkitAgent
├── resources.qrc           # Recursos QML embarcados
├── sim_32x32.xpm           # Ícone do app
└── qml/                    # Interface QML
    ├── StkMenu.qml         # Menu principal (ListView)
    ├── StkView.qml         # View base com título/ícone/panels
    ├── StkPanel.qml        # Painel End/Back
    ├── StkButton.qml       # Botão customizado
    ├── StkInputText.qml    # Entrada de texto
    ├── StkPassword.qml     # Entrada de senha
    ├── StkPopup.qml        # Popup genérico
    ├── StkYesNo.qml        # Sim/Não
    ├── StkWebView.qml      # Visualizador web
    └── StkPlaySound.qml    # Reprodutor de som
```

## Stack alvo

- **Qt 6** (QQuickView, QtQuick 2.15, QDBusAbstractInterface)
- C++17
- CMake 3.16+

No momento, o `CMakeLists.txt` está configurado para **Qt 5.15** (disponível em muitas distros) para facilitar a compilação imediata. Para migrar para Qt 6, basta trocar `find_package(Qt5` → `find_package(Qt6` e `Qt5::` → `Qt6::`.

## Build

```bash
# Instalar dependências (exemplo Arch/Manjaro):
# sudo pacman -S qt5-base qt5-declarative qt5-multimedia qt5-tools

cd satk-qt6
mkdir -p build && cd build
cmake ..
make
./satk          # modo menu
./satk agent    # modo agente (background, D-Bus)
```

## Dependências de runtime

- D-Bus do sistema (system bus)
- oFono (org.ofono.Manager, org.ofono.Modem, org.ofono.SimManager, org.ofono.SimToolkit)
- Acesso ao modem SIM via oFono

## Próximos passos (piloto)

1. Instalar Qt 5 ou Qt 6 no ambiente de build
2. Compilar e testar `./satk menu`
3. Implementar leitura real de menus SIM via D-Bus em `stkofonoutils.cpp` e `stkofonoproperties.cpp`
4. Conectar sinais QML aos slots C++ para interatividade completa
5. Empacotar como `.deb` para distribuição via OpenRepos / MeeShopGUI

## Licença

Apache License 2.0 (mesma do original).
