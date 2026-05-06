"""
app.py - Interface Web do Patrobook (Bonus)
Servidor Flask que fornece uma API REST e interface grafica web
para o simulador de rede social Patrobook.

Trabalho Final - Algoritmos e Estruturas de Dados (PIT)
"""

from flask import Flask, render_template, request, jsonify
import json
import os

app = Flask(__name__)

DATA_FILE = os.path.join(os.path.dirname(os.path.abspath(__file__)), '..', 'patrobook_web.json')


def carregar_dados():
    """Carrega os dados do arquivo JSON."""
    if os.path.exists(DATA_FILE):
        with open(DATA_FILE, 'r', encoding='utf-8') as f:
            return json.load(f)
    return {'usuarios': [], 'proximo_id': 1}


def salvar_dados(dados):
    """Salva os dados no arquivo JSON."""
    with open(DATA_FILE, 'w', encoding='utf-8') as f:
        json.dump(dados, f, indent=2, ensure_ascii=False)


@app.route('/')
def index():
    """Pagina principal do Patrobook."""
    return render_template('index.html')


# ==================== API REST ====================

@app.route('/api/usuarios', methods=['GET'])
def listar_usuarios():
    """Lista todos os usuarios."""
    dados = carregar_dados()
    return jsonify(dados['usuarios'])


@app.route('/api/usuarios', methods=['POST'])
def adicionar_usuario():
    """Adiciona um novo usuario."""
    dados = carregar_dados()
    body = request.get_json()

    nome = body.get('nome', '').strip()
    idade = body.get('idade', 0)

    if not nome:
        return jsonify({'erro': 'Nome nao pode ser vazio.'}), 400
    if not isinstance(idade, int) or idade <= 0 or idade > 150:
        return jsonify({'erro': 'Idade deve ser entre 1 e 150.'}), 400

    usuario = {
        'id': dados['proximo_id'],
        'nome': nome,
        'idade': idade,
        'amigos': []
    }

    dados['proximo_id'] += 1
    dados['usuarios'].append(usuario)
    salvar_dados(dados)

    return jsonify(usuario), 201


@app.route('/api/usuarios/<int:uid>', methods=['DELETE'])
def remover_usuario(uid):
    """Remove um usuario e todas as suas amizades."""
    dados = carregar_dados()

    usuario = next((u for u in dados['usuarios'] if u['id'] == uid), None)
    if not usuario:
        return jsonify({'erro': f'Usuario com ID {uid} nao encontrado.'}), 404

    nome = usuario['nome']

    # Remover o usuario da lista de amigos de todos os outros
    for u in dados['usuarios']:
        if uid in u['amigos']:
            u['amigos'].remove(uid)

    # Remover o usuario
    dados['usuarios'] = [u for u in dados['usuarios'] if u['id'] != uid]
    salvar_dados(dados)

    return jsonify({'mensagem': f'Perfil de "{nome}" removido com sucesso.'})


@app.route('/api/amizades', methods=['POST'])
def criar_amizade():
    """Cria uma amizade bidirecional entre dois usuarios."""
    dados = carregar_dados()
    body = request.get_json()

    id1 = body.get('id1')
    id2 = body.get('id2')

    if id1 == id2:
        return jsonify({'erro': 'Voce nao pode ser amigo de si mesmo!'}), 400

    u1 = next((u for u in dados['usuarios'] if u['id'] == id1), None)
    u2 = next((u for u in dados['usuarios'] if u['id'] == id2), None)

    if not u1:
        return jsonify({'erro': f'Usuario com ID {id1} nao encontrado.'}), 404
    if not u2:
        return jsonify({'erro': f'Usuario com ID {id2} nao encontrado.'}), 404

    if id2 in u1['amigos']:
        return jsonify({'erro': f'{u1["nome"]} e {u2["nome"]} ja sao amigos!'}), 400

    u1['amigos'].append(id2)
    u2['amigos'].append(id1)
    salvar_dados(dados)

    return jsonify({
        'mensagem': f'Amizade criada entre {u1["nome"]} e {u2["nome"]}!'
    }), 201


@app.route('/api/amizades', methods=['DELETE'])
def remover_amizade():
    """Remove a amizade entre dois usuarios."""
    dados = carregar_dados()
    body = request.get_json()

    id1 = body.get('id1')
    id2 = body.get('id2')

    u1 = next((u for u in dados['usuarios'] if u['id'] == id1), None)
    u2 = next((u for u in dados['usuarios'] if u['id'] == id2), None)

    if not u1:
        return jsonify({'erro': f'Usuario com ID {id1} nao encontrado.'}), 404
    if not u2:
        return jsonify({'erro': f'Usuario com ID {id2} nao encontrado.'}), 404

    if id2 not in u1['amigos']:
        return jsonify({'erro': f'{u1["nome"]} e {u2["nome"]} nao sao amigos.'}), 400

    u1['amigos'].remove(id2)
    u2['amigos'].remove(id1)
    salvar_dados(dados)

    return jsonify({
        'mensagem': f'Amizade removida entre {u1["nome"]} e {u2["nome"]}.'
    })


@app.route('/api/usuarios/<int:uid>/amigos', methods=['GET'])
def listar_amigos(uid):
    """Lista os amigos de um usuario."""
    dados = carregar_dados()

    usuario = next((u for u in dados['usuarios'] if u['id'] == uid), None)
    if not usuario:
        return jsonify({'erro': f'Usuario com ID {uid} nao encontrado.'}), 404

    amigos = [u for u in dados['usuarios'] if u['id'] in usuario['amigos']]

    return jsonify({
        'usuario': usuario['nome'],
        'total': len(amigos),
        'amigos': amigos
    })


if __name__ == '__main__':
    print("\n🌐 Patrobook Web Interface")
    print("   Acesse: http://localhost:5000\n")
    app.run(debug=True, port=5000)
