# NBioBSP para Python
### Módulo beta para integração do SDK NBioBSP com Python
Este é um módulo Python para o SDK NBioBSP. Construído com C/C++ e pybind11.
**Funciona apenas no Windows no momento.**

**Todo o código está contido em um único arquivo, pois são apenas bindings.**

## Requisitos
- Python 3.10 ou superior
- eNBSP SDK maior ou igual a 5.2
- MSVC 2019 ou superior (talvez funcione com outro compilador, ainda não testei)
- Cmake 20 ou superior

## A fazer:
- [x] Saída de erro legível usando tipos NBioAPI **(prioridade)**
- [x] Lidar com erros adequadamente
    - [x] Lançar exceções traduzíveis e adequadas de C++ para Python
- [x] Lidar com valores de retorno adequadamente **(prioridade)**
- [x] Lidar com propósitos de impressão digital na captura adequadamente
- [x] Implementar métodos IndexSearch
- [ ] Implementar todas as funções que são possíveis no Windows
- [ ] Implementar todas as funções que são *possíveis* no Linux **(sem prioridade)**

Você pode testar o módulo com o seguinte código:

```python
import nbsp_python as nbsp

# Inicialize a instância NBioBSP
nbsp.initialize_handle()

# Obtenha a versão do SDK NBioBSP
nbsp.get_version()

# Enumere os dispositivos conectados ao computador
nbsp.enumerate_device()

# Abra o dispositivo usando a detecção automática
nbsp.open_device()

# Capture uma impressão digital e atribua-a ao handle
handle = nbsp.capture("enroll", 10000)

# Verifique as impressões digitais contidas no handle
nbsp.verify(handle)

# Extraia o hash da última impressão digital adicionada ao handle
fingerprint_hash = nbsp.extract_fir_text(handle)

# Inicialize a pesquisa de índice
nbsp.init_index_search()

# Adicione a impressão digital à pesquisa de índice e passe
nbsp.add_fir_to_index_search(fingerprint_hash, 1)

# Identifique a impressão digital na pesquisa de índice
nbsp.identify_data_from_index_search(fingerprint_hash)

# Encerre a pesquisa de índice
nbsp.terminate_index_search()

# Encerre a instância NBioBSP
nbsp.terminate_handle()

# Feche o dispositivo
nbsp.close_device()
```
Ou executando o exemplo em [TKinter](example/tkinter_example.py)

## Instalação

```python
git clone https://github.com/Andoreatta/nbsp-python.git
cd nbsp-python
pip install .
```
Puxa todas as dependências e instala o módulo.

-----------------
## Usage

- `nbsp.initialize()`
    Inicializa a instância NBioBSP. Deve ser chamado antes de qualquer outra função que interaja com o dispositivo.
    Portanto, você pode chamar get_version() antes de initialize(), mas não capture(). Retorna um identificador caso necessário.

- `nbsp.terminate()`
    Encerra a instância NBioBSP.

- `nbsp.get_version()`
    Retorna a versão do SDK NBioBSP.

- `nbsp.enumerate_device()`
    Enumera os dispositivos conectados ao computador. Retorna uma lista de dispositivos.

- `nbsp.open_device()`
    Abre o dispositivo usando a detecção automática. Retorna o identificador do dispositivo.

- `nbsp.open_specific_device(index)`
    Abre o dispositivo usando o ID do dispositivo. Retorna true se bem sucedido.

- `nbsp.close_device()`
    Fecha o dispositivo.


- `nbsp.capture("purpose", timeout)`
    Captura uma impressão digital. Retorna o identificador da impressão digital.
    `purpose` pode ser um dos seguintes:
    - `"enroll"`
        para registrar uma impressão digital
    - `"verify"`
        para verificar uma impressão digital
    - `"identify"`
        para identificar uma impressão digital
    - `"enroll_for_verification"`
        para registrar uma impressão digital para verificação
    - `"enroll_for_identification"`
        para registrar uma impressão digital para identificação

- `nbsp.verify(handle)`
    Verifica uma impressão digital. Retorna true se bem sucedido.

- `nbsp.extract_fir_text(handle)`
    Extrai o hash da impressão digital do identificador. Retorna o hash da impressão digital.

- `nbsp.init_index_search()`
    Inicializa a engine de pesquisa interna.

- `nbsp.terminate_index_search()`
    Encerra a engine de pesquisa interna.

- `nbsp.add_fir_to_index_search(fingerprint_hash, user_id)`
    Adiciona a impressão digital à engine de pesquisa interna. Retorna true se bem sucedido.
