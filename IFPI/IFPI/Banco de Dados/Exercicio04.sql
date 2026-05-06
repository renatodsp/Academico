-- ============================================================
-- I. CRIAÇÃO DO BANCO DE DADOS E TABELAS
-- ============================================================

DROP DATABASE IF EXISTS publicacoes;
CREATE DATABASE publicacoes CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci;
USE publicacoes;

-- Tabela NACIONALIDADE
CREATE TABLE NACIONALIDADE (
    codigo INT PRIMARY KEY AUTO_INCREMENT,
    pais VARCHAR(100) NOT NULL
);

-- Tabela ASSUNTO
CREATE TABLE ASSUNTO (
    codigo INT PRIMARY KEY AUTO_INCREMENT,
    descricao VARCHAR(150) NOT NULL
);

-- Tabela EDITORA
CREATE TABLE EDITORA (
    codigo INT PRIMARY KEY AUTO_INCREMENT,
    cnpj VARCHAR(18) NOT NULL UNIQUE,
    nome VARCHAR(150) NOT NULL
);

-- Tabela AUTOR
CREATE TABLE AUTOR (
    codigo INT PRIMARY KEY AUTO_INCREMENT,
    nome VARCHAR(150) NOT NULL,
    passaporte VARCHAR(20) UNIQUE,
    datanascimento DATE,
    nacionalidade_codigo INT,
    FOREIGN KEY (nacionalidade_codigo) REFERENCES NACIONALIDADE(codigo)
);

-- Tabela LIVRO
CREATE TABLE LIVRO (
    codigo INT PRIMARY KEY AUTO_INCREMENT,
    isbn VARCHAR(20) NOT NULL UNIQUE,
    titulo VARCHAR(200) NOT NULL,
    preco DECIMAL(10,2),
    datalancamento DATE,
    assunto_codigo INT,
    editora_codigo INT,
    FOREIGN KEY (assunto_codigo) REFERENCES ASSUNTO(codigo),
    FOREIGN KEY (editora_codigo) REFERENCES EDITORA(codigo)
);

-- Tabela AUTOR_LIVRO
CREATE TABLE AUTOR_LIVRO (
    autor_codigo INT,
    livro_codigo INT,
    PRIMARY KEY (autor_codigo, livro_codigo),
    FOREIGN KEY (autor_codigo) REFERENCES AUTOR(codigo),
    FOREIGN KEY (livro_codigo) REFERENCES LIVRO(codigo)
);

-- ============================================================
-- II. INSERÇÃO DE DADOS
-- ============================================================

-- NACIONALIDADE
INSERT INTO NACIONALIDADE (codigo, pais) VALUES
(1, 'Brasil'),
(2, 'Estados Unidos'),
(3, 'Inglaterra'),
(4, 'Portugal'),
(5, 'Argentina');

-- ASSUNTO
INSERT INTO ASSUNTO (codigo, descricao) VALUES
(1, 'Banco de Dados'),
(2, 'Estruturas de Dados'),
(3, 'Programação'),
(4, 'Redes de Computadores'),
(5, 'Inteligência Artificial'),
(6, 'Engenharia de Software'),
(7, 'Sistemas Operacionais');

-- EDITORA
INSERT INTO EDITORA (codigo, cnpj, nome) VALUES
(1, '11.111.111/0001-11', 'Books Editora'),
(2, '22.222.222/0001-22', 'Editora Moderna'),
(3, '33.333.333/0001-33', 'Tech Books Editora'),
(4, '44.444.444/0001-44', 'Editora Acadêmica'),
(5, '55.555.555/0001-55', 'Editora Nacional');

-- AUTOR
INSERT INTO AUTOR (codigo, nome, passaporte, datanascimento, nacionalidade_codigo) VALUES
(1, 'Machado de Assis', 'BR001', '1839-06-21', 1),
(2, 'João da Silva', 'BR002', '1975-03-15', 1),
(3, 'Carlos Luis Pereira', 'BR003', '1980-07-22', 1),
(4, 'John Smith', 'US001', '1965-11-30', 2),
(5, 'James Martin', 'UK001', '1915-04-10', 3),
(6, 'João Pedro Santos', 'BR004', '1945-08-05', 1),
(7, 'Maria Oliveira', 'BR005', '1990-02-18', 1),
(8, 'Roberto Carlos Luis', 'BR006', '1972-09-12', 1),
(9, 'Pedro Alvares', 'PT001', '1918-01-25', 4),
(10, 'Diego Martinez', 'AR001', '1988-05-30', 5);

-- LIVRO
INSERT INTO LIVRO (codigo, isbn, titulo, preco, datalancamento, assunto_codigo, editora_codigo) VALUES
(1, '978-85-0001', 'Banco de Dados Relacional', 89.90, '2018-03-15', 1, 1),
(2, '978-85-0002', 'Estruturas de Dados em C', 55.00, '2019-06-20', 2, 2),
(3, '978-85-0003', 'Programação em Python', 45.00, '2020-01-10', 3, 1),
(4, '978-85-0004', 'Redes de Computadores Avançadas', 120.50, '2017-08-05', 4, 3),
(5, '978-85-0005', 'Banco de Dados NoSQL', 150.00, '2021-02-28', 1, 1),
(6, '978-85-0006', 'Inteligência Artificial Moderna', 200.00, '2019-11-15', 5, 4),
(7, '978-85-0007', 'Bancos de Dados Distribuídos', 75.00, '2020-05-20', 1, 2),
(8, '978-85-0008', 'Algoritmos e Estruturas de Dados', 60.00, '2018-09-10', 2, 3),
(9, '978-85-0009', 'Engenharia de Software Prática', 95.00, '2021-07-01', 6, 4),
(10, '978-85-0010', 'Sistemas Operacionais Modernos', 110.00, '2016-04-12', 7, 5),
(11, '978-85-0011', 'Banco de Dados Oracle', 180.00, NULL, 1, 3),
(12, '978-85-0012', 'Programação Java Avançada', 70.00, '2020-10-05', 3, 2),
(13, '978-85-0013', 'Redes sem Fio', 35.00, '2019-03-22', 4, 5),
(14, '978-85-0014', 'Banco de Dados e SQL', 42.00, '2021-01-15', 1, 1),
(15, '978-85-0015', 'Fundamentos de Banco de Dados', 55.00, NULL, 1, 2),
(16, '978-85-0016', 'Introdução à Programação', 30.00, '2020-06-18', 3, 4),
(17, '978-85-0017', 'Compiladores e Dados', 65.00, '2019-12-01', 3, 3),
(18, '978-85-0018', 'Machine Learning Avançado', 250.00, NULL, 5, 5),
(19, '978-85-0019', 'Lógica de Programação', 28.00, '2021-09-10', 3, 1),
(20, '978-85-0020', 'Segurança em Redes', 48.00, '2020-04-25', 4, 2);

-- AUTOR_LIVRO
INSERT INTO AUTOR_LIVRO (autor_codigo, livro_codigo) VALUES
(1, 1), (1, 5),
(2, 1), (2, 7), (2, 14),
(3, 2), (3, 8), (3, 17),
(4, 3), (4, 12),
(5, 4), (5, 10),
(6, 5), (6, 11),
(7, 6), (7, 9), (7, 18),
(8, 7), (8, 15),
(9, 8), (9, 13),
(10, 9), (10, 20),
(2, 16), (3, 19),
(4, 6),
(1, 14);

-- ============================================================
-- III. CONSULTAS (1 a 75)
-- ============================================================

-- 1. Livros que possuam preços superiores a R$ 50,00.
SELECT * FROM LIVRO WHERE preco > 50.00;

-- 2. Livros que possuam preços entre R$ 100,00 e R$ 200,00.
SELECT * FROM LIVRO WHERE preco BETWEEN 100.00 AND 200.00;

-- 3. Livros cujos títulos possuam a palavra 'Banco'.
SELECT * FROM LIVRO WHERE titulo LIKE '%Banco%';

-- 4. Livros cujos títulos iniciam com a palavra 'Banco'.
SELECT * FROM LIVRO WHERE titulo LIKE 'Banco%';

-- 5. Livros cujos títulos terminam com a palavra 'Dados'.
SELECT * FROM LIVRO WHERE titulo LIKE '%Dados';

-- 6. Livros cujos títulos possuem a expressão 'Banco de Dados' ou 'Bancos de Dados'.
SELECT * FROM LIVRO WHERE titulo LIKE '%Banco de Dados%' OR titulo LIKE '%Bancos de Dados%';

-- 7. Livros que foram lançados há mais de 5 anos.
SELECT * FROM LIVRO WHERE datalancamento < DATE_SUB(CURDATE(), INTERVAL 5 YEAR);

-- 8. Livros que ainda não foram lançados, ou seja, com a data de lançamento nula.
SELECT * FROM LIVRO WHERE datalancamento IS NULL;

-- 9. Livros cujo assunto seja 'Estruturas de Dados'.
SELECT L.* FROM LIVRO L
JOIN ASSUNTO A ON L.assunto_codigo = A.codigo
WHERE A.descricao = 'Estruturas de Dados';

-- 10. Livros cujo assunto tenha código 1, 2 ou 3.
SELECT * FROM LIVRO WHERE assunto_codigo IN (1, 2, 3);

-- 11. Quantidade de livros.
SELECT COUNT(*) AS quantidade_livros FROM LIVRO;

-- 12. Quantidade de livros que ainda não foram lançados.
SELECT COUNT(*) AS quantidade_nao_lancados FROM LIVRO WHERE datalancamento IS NULL;

-- 13. Soma dos preços dos livros.
SELECT SUM(preco) AS soma_precos FROM LIVRO;

-- 14. Média de preços dos livros.
SELECT AVG(preco) AS media_precos FROM LIVRO;

-- 15. Maior preço dos livros.
SELECT MAX(preco) AS maior_preco FROM LIVRO;

-- 16. Menor preço dos livros.
SELECT MIN(preco) AS menor_preco FROM LIVRO;

-- 17. O preço médio dos livros para cada assunto.
SELECT A.descricao, AVG(L.preco) AS preco_medio
FROM LIVRO L
JOIN ASSUNTO A ON L.assunto_codigo = A.codigo
GROUP BY A.descricao;

-- 18. Quantidade de livros para cada assunto.
SELECT A.descricao, COUNT(*) AS quantidade
FROM LIVRO L
JOIN ASSUNTO A ON L.assunto_codigo = A.codigo
GROUP BY A.descricao;

-- 19. O preço do livro mais caro de cada assunto, dentre aqueles que já foram lançados.
SELECT A.descricao, MAX(L.preco) AS preco_maximo
FROM LIVRO L
JOIN ASSUNTO A ON L.assunto_codigo = A.codigo
WHERE L.datalancamento IS NOT NULL
GROUP BY A.descricao;

-- 20. Quantidade de livros lançados por editora.
SELECT E.nome, COUNT(*) AS quantidade
FROM LIVRO L
JOIN EDITORA E ON L.editora_codigo = E.codigo
WHERE L.datalancamento IS NOT NULL
GROUP BY E.nome;

-- 21. Assuntos cujo preço médio dos livros ultrapassa R$ 50,00.
SELECT A.descricao, AVG(L.preco) AS preco_medio
FROM LIVRO L
JOIN ASSUNTO A ON L.assunto_codigo = A.codigo
GROUP BY A.descricao
HAVING AVG(L.preco) > 50.00;

-- 22. Assuntos que possuem pelo menos 2 livros.
SELECT A.descricao, COUNT(*) AS quantidade
FROM LIVRO L
JOIN ASSUNTO A ON L.assunto_codigo = A.codigo
GROUP BY A.descricao
HAVING COUNT(*) >= 2;

-- 23. Assuntos que possuem pelo menos 2 livros já lançados.
SELECT A.descricao, COUNT(*) AS quantidade
FROM LIVRO L
JOIN ASSUNTO A ON L.assunto_codigo = A.codigo
WHERE L.datalancamento IS NOT NULL
GROUP BY A.descricao
HAVING COUNT(*) >= 2;

-- 24. Quantidade de livros lançados por assunto.
SELECT A.descricao, COUNT(*) AS quantidade
FROM LIVRO L
JOIN ASSUNTO A ON L.assunto_codigo = A.codigo
WHERE L.datalancamento IS NOT NULL
GROUP BY A.descricao;

-- 25. Nome e passaporte dos autores que possuem a palavra 'João' no nome.
SELECT nome, passaporte FROM AUTOR WHERE nome LIKE '%João%';

-- 26. Nome e passaporte dos autores que nasceram após 1° de janeiro de 1970.
SELECT nome, passaporte FROM AUTOR WHERE datanascimento > '1970-01-01';

-- 27. Nome e passaporte dos autores que não são brasileiros.
SELECT A.nome, A.passaporte
FROM AUTOR A
JOIN NACIONALIDADE N ON A.nacionalidade_codigo = N.codigo
WHERE N.pais <> 'Brasil';

-- 28. Quantidade de autores.
SELECT COUNT(*) AS quantidade_autores FROM AUTOR;

-- 29. Quantidade média de autores dos livros.
SELECT AVG(qtd_autores) AS media_autores
FROM (
    SELECT livro_codigo, COUNT(*) AS qtd_autores
    FROM AUTOR_LIVRO
    GROUP BY livro_codigo
) AS sub;

-- 30. Livros que possuem ao menos 2 autores.
SELECT L.titulo, COUNT(AL.autor_codigo) AS qtd_autores
FROM LIVRO L
JOIN AUTOR_LIVRO AL ON L.codigo = AL.livro_codigo
GROUP BY L.titulo
HAVING COUNT(AL.autor_codigo) >= 2;

-- 31. Preço médio dos livros por editora.
SELECT E.nome, AVG(L.preco) AS preco_medio
FROM LIVRO L
JOIN EDITORA E ON L.editora_codigo = E.codigo
GROUP BY E.nome;

-- 32. Preço máximo, preço mínimo e preço médio dos livros cujos códigos do assunto são 1, 2 ou 3, para cada editora.
SELECT E.nome,
       MAX(L.preco) AS preco_maximo,
       MIN(L.preco) AS preco_minimo,
       AVG(L.preco) AS preco_medio
FROM LIVRO L
JOIN EDITORA E ON L.editora_codigo = E.codigo
WHERE L.assunto_codigo IN (1, 2, 3)
GROUP BY E.nome;

-- 33. Quantidade de autores para cada nacionalidade.
SELECT N.pais, COUNT(*) AS quantidade
FROM AUTOR A
JOIN NACIONALIDADE N ON A.nacionalidade_codigo = N.codigo
GROUP BY N.pais;

-- 34. Quantidade de autores que nasceram antes de 1° de janeiro de 1920, para cada nacionalidade.
SELECT N.pais, COUNT(*) AS quantidade
FROM AUTOR A
JOIN NACIONALIDADE N ON A.nacionalidade_codigo = N.codigo
WHERE A.datanascimento < '1920-01-01'
GROUP BY N.pais;

-- 35. A data de nascimento do autor mais velho.
SELECT MIN(datanascimento) AS autor_mais_velho FROM AUTOR;

-- 36. A data de nascimento do autor mais novo.
SELECT MAX(datanascimento) AS autor_mais_novo FROM AUTOR;

-- 37. Os novos preços dos livros se os valores fossem reajustados em 10%.
SELECT titulo, preco, ROUND(preco * 1.10, 2) AS novo_preco FROM LIVRO;

-- 38. O dia da publicação do livro de código 1.
SELECT DAY(datalancamento) AS dia_publicacao FROM LIVRO WHERE codigo = 1;

-- 39. O mês e o ano da publicação dos livros cujo assunto tem código 1.
SELECT titulo, MONTH(datalancamento) AS mes, YEAR(datalancamento) AS ano
FROM LIVRO
WHERE assunto_codigo = 1;

-- 40. Quantidade de autores distintos que estão associados a livros na tabela AUTOR_LIVRO.
SELECT COUNT(DISTINCT autor_codigo) AS autores_distintos FROM AUTOR_LIVRO;

-- 41. Título, assunto e preço, ordenado em ordem crescente por assunto e decrescente por preço.
SELECT L.titulo, A.descricao AS assunto, L.preco
FROM LIVRO L
JOIN ASSUNTO A ON L.assunto_codigo = A.codigo
ORDER BY A.descricao ASC, L.preco DESC;

-- 42. Editoras ordenadas alfabeticamente. A coluna de nomes deve ter a palavra 'Editora' como título.
SELECT nome AS 'Editora' FROM EDITORA ORDER BY nome ASC;

-- 43. Preços e os títulos dos livros, em ordem decrescente de preço.
SELECT preco, titulo FROM LIVRO ORDER BY preco DESC;

-- 44. Editoras que já publicaram livros, sem repetições.
SELECT DISTINCT E.nome
FROM EDITORA E
JOIN LIVRO L ON E.codigo = L.editora_codigo;

-- 45. Autores brasileiros com mês e ano de nascimento, por ordem decrescente de idade e por ordem crescente de nome do autor.
SELECT A.nome, MONTH(A.datanascimento) AS mes, YEAR(A.datanascimento) AS ano
FROM AUTOR A
JOIN NACIONALIDADE N ON A.nacionalidade_codigo = N.codigo
WHERE N.pais = 'Brasil'
ORDER BY A.datanascimento ASC, A.nome ASC;

-- 46. Editora (nome), assunto (código) e quantidade (livros publicados pela editora para cada assunto) em ordem decrescente de quantidade.
SELECT E.nome AS editora, L.assunto_codigo AS assunto, COUNT(*) AS quantidade
FROM LIVRO L
JOIN EDITORA E ON L.editora_codigo = E.codigo
GROUP BY E.nome, L.assunto_codigo
ORDER BY quantidade DESC;

-- 47. Títulos cujo título tenha comprimento superior a 15 caracteres.
SELECT titulo FROM LIVRO WHERE CHAR_LENGTH(titulo) > 15;

-- 48. Títulos dos livros já lançados e a descrição dos seus assuntos.
SELECT L.titulo, A.descricao
FROM LIVRO L
JOIN ASSUNTO A ON L.assunto_codigo = A.codigo
WHERE L.datalancamento IS NOT NULL;

-- 49. Título do livro, nome da editora que o publicou e a descrição do assunto.
SELECT L.titulo, E.nome AS editora, A.descricao AS assunto
FROM LIVRO L
JOIN EDITORA E ON L.editora_codigo = E.codigo
JOIN ASSUNTO A ON L.assunto_codigo = A.codigo;

-- 50. Editoras e títulos dos livros lançados pela editora, ordenada por nome da editora e pelo título do livro.
SELECT E.nome AS editora, L.titulo
FROM EDITORA E
JOIN LIVRO L ON E.codigo = L.editora_codigo
WHERE L.datalancamento IS NOT NULL
ORDER BY E.nome, L.titulo;

-- 51. Editoras cadastradas e para aquelas que possuem livros publicados, relacionar também o título do livro, em ordem de nome da editora e pelo título do livro.
SELECT E.nome AS editora, L.titulo
FROM EDITORA E
LEFT JOIN LIVRO L ON E.codigo = L.editora_codigo
ORDER BY E.nome, L.titulo;

-- 52. Assuntos, contendo os títulos dos livros dos respectivos assuntos, ordenada pela descrição do assunto.
SELECT A.descricao AS assunto, L.titulo
FROM ASSUNTO A
JOIN LIVRO L ON A.codigo = L.assunto_codigo
ORDER BY A.descricao;

-- 53. Títulos e editoras, relacionando a obra com a editora que a publica, quando for o caso.
SELECT L.titulo, E.nome AS editora
FROM LIVRO L
LEFT JOIN EDITORA E ON L.editora_codigo = E.codigo;

-- 54. Descrição de todos os assuntos e os títulos dos livros de cada um. Quando não existir um livro associado ao assunto, escrever 'Sem publicações'.
SELECT A.descricao, COALESCE(L.titulo, 'Sem publicações') AS titulo
FROM ASSUNTO A
LEFT JOIN LIVRO L ON A.codigo = L.assunto_codigo;

-- 55. Nomes dos autores e os livros de sua autoria, ordenada pelo nome do autor.
SELECT AU.nome, L.titulo
FROM AUTOR AU
JOIN AUTOR_LIVRO AL ON AU.codigo = AL.autor_codigo
JOIN LIVRO L ON AL.livro_codigo = L.codigo
ORDER BY AU.nome;

-- 56. Editoras que publicaram livros escritos pelo autor 'Machado de Assis'.
SELECT DISTINCT E.nome
FROM EDITORA E
JOIN LIVRO L ON E.codigo = L.editora_codigo
JOIN AUTOR_LIVRO AL ON L.codigo = AL.livro_codigo
JOIN AUTOR AU ON AL.autor_codigo = AU.codigo
WHERE AU.nome = 'Machado de Assis';

-- 57. Quantidade de livros lançados que foram escritos por um autor cujo nome possui a palavra 'Luis'.
SELECT COUNT(DISTINCT L.codigo) AS quantidade
FROM LIVRO L
JOIN AUTOR_LIVRO AL ON L.codigo = AL.livro_codigo
JOIN AUTOR AU ON AL.autor_codigo = AU.codigo
WHERE AU.nome LIKE '%Luis%'
AND L.datalancamento IS NOT NULL;

-- 58. O preço do livro mais caro publicado pela editora 'Books Editora' sobre banco de dados.
SELECT MAX(L.preco) AS preco_mais_caro
FROM LIVRO L
JOIN EDITORA E ON L.editora_codigo = E.codigo
JOIN ASSUNTO A ON L.assunto_codigo = A.codigo
WHERE E.nome = 'Books Editora'
AND A.descricao = 'Banco de Dados';

-- 59. Editoras que não publicaram livros.
SELECT E.nome
FROM EDITORA E
LEFT JOIN LIVRO L ON E.codigo = L.editora_codigo
WHERE L.codigo IS NULL;

-- 60. Título do livro e o nome da editora que o publica para todos os livros que custam menos que R$ 50,00.
SELECT L.titulo, E.nome AS editora
FROM LIVRO L
JOIN EDITORA E ON L.editora_codigo = E.codigo
WHERE L.preco < 50.00;

-- 61. Nome e passaporte do autor brasileiro que tenha nascido antes de 1° de janeiro de 1950 e os títulos dos livros de sua autoria, ordenado pelo nome do autor e pelo título do livro.
SELECT AU.nome, AU.passaporte, L.titulo
FROM AUTOR AU
JOIN NACIONALIDADE N ON AU.nacionalidade_codigo = N.codigo
JOIN AUTOR_LIVRO AL ON AU.codigo = AL.autor_codigo
JOIN LIVRO L ON AL.livro_codigo = L.codigo
WHERE N.pais = 'Brasil'
AND AU.datanascimento < '1950-01-01'
ORDER BY AU.nome, L.titulo;

-- 62. Nome e passaporte do autor e o preço máximo dos livros de sua autoria.
SELECT AU.nome, AU.passaporte, MAX(L.preco) AS preco_maximo
FROM AUTOR AU
JOIN AUTOR_LIVRO AL ON AU.codigo = AL.autor_codigo
JOIN LIVRO L ON AL.livro_codigo = L.codigo
GROUP BY AU.nome, AU.passaporte;

-- 63. Nome do autor e nome da editora que já lançaram pelo menos 2 livros.
SELECT AU.nome AS autor, E.nome AS editora
FROM AUTOR AU
JOIN AUTOR_LIVRO AL ON AU.codigo = AL.autor_codigo
JOIN LIVRO L ON AL.livro_codigo = L.codigo
JOIN EDITORA E ON L.editora_codigo = E.codigo
WHERE L.datalancamento IS NOT NULL
GROUP BY AU.nome, E.nome
HAVING COUNT(L.codigo) >= 2;

-- 64. Descrição do assunto referenciado em pelo menos 10 livros.
SELECT A.descricao
FROM ASSUNTO A
JOIN LIVRO L ON A.codigo = L.assunto_codigo
GROUP BY A.descricao
HAVING COUNT(L.codigo) >= 10;

-- 65. Nomes das editoras que possuem livros lançados.
SELECT DISTINCT E.nome
FROM EDITORA E
JOIN LIVRO L ON E.codigo = L.editora_codigo
WHERE L.datalancamento IS NOT NULL;

-- 66. Assuntos para os quais não foram lançados livros.
SELECT A.descricao
FROM ASSUNTO A
LEFT JOIN LIVRO L ON A.codigo = L.assunto_codigo AND L.datalancamento IS NOT NULL
WHERE L.codigo IS NULL;

-- 67. Descrição dos assuntos e quantidade de livros lançados de cada um.
SELECT A.descricao, COUNT(L.codigo) AS quantidade
FROM ASSUNTO A
LEFT JOIN LIVRO L ON A.codigo = L.assunto_codigo AND L.datalancamento IS NOT NULL
GROUP BY A.descricao;

-- 68. Nome das editoras e o preço médio dos livros de cada uma.
SELECT E.nome, AVG(L.preco) AS preco_medio
FROM EDITORA E
JOIN LIVRO L ON E.codigo = L.editora_codigo
GROUP BY E.nome;

-- 69. Nome das editoras e os livros das editoras que lançaram ao menos 2 livros, ordenados pelo nome da editora e pelo título da publicação.
SELECT E.nome AS editora, L.titulo
FROM EDITORA E
JOIN LIVRO L ON E.codigo = L.editora_codigo
WHERE L.datalancamento IS NOT NULL
AND E.codigo IN (
    SELECT editora_codigo
    FROM LIVRO
    WHERE datalancamento IS NOT NULL
    GROUP BY editora_codigo
    HAVING COUNT(*) >= 2
)
ORDER BY E.nome, L.titulo;

-- 70. Títulos dos livros dos assuntos cujo preço médio do livro é superior a R$ 40,00, juntamente com os respectivos assuntos.
SELECT L.titulo, A.descricao AS assunto
FROM LIVRO L
JOIN ASSUNTO A ON L.assunto_codigo = A.codigo
WHERE L.assunto_codigo IN (
    SELECT assunto_codigo
    FROM LIVRO
    GROUP BY assunto_codigo
    HAVING AVG(preco) > 40.00
);

-- 71. Títulos dos livros cujo assunto é 'Banco de Dados' ou que foram lançados por editoras que contenham 'Books' no nome.
SELECT DISTINCT L.titulo
FROM LIVRO L
JOIN ASSUNTO A ON L.assunto_codigo = A.codigo
JOIN EDITORA E ON L.editora_codigo = E.codigo
WHERE A.descricao = 'Banco de Dados'
OR E.nome LIKE '%Books%';

-- 72. Títulos dos livros cujo assunto é 'Banco de Dados' e que foram lançados por editoras que contenham 'Books' no nome.
SELECT L.titulo
FROM LIVRO L
JOIN ASSUNTO A ON L.assunto_codigo = A.codigo
JOIN EDITORA E ON L.editora_codigo = E.codigo
WHERE A.descricao = 'Banco de Dados'
AND E.nome LIKE '%Books%';

-- 73. Títulos dos livros cujo assunto é 'Banco de Dados' e que não foram lançados por editoras que contenham 'Books' no nome.
SELECT L.titulo
FROM LIVRO L
JOIN ASSUNTO A ON L.assunto_codigo = A.codigo
JOIN EDITORA E ON L.editora_codigo = E.codigo
WHERE A.descricao = 'Banco de Dados'
AND E.nome NOT LIKE '%Books%';

-- 74. Títulos dos livros que não foram lançados por editoras que contenham 'Books' no nome cujo assunto é 'Banco de Dados'.
SELECT L.titulo
FROM LIVRO L
JOIN ASSUNTO A ON L.assunto_codigo = A.codigo
JOIN EDITORA E ON L.editora_codigo = E.codigo
WHERE E.nome NOT LIKE '%Books%'
AND A.descricao = 'Banco de Dados';

-- 75. Excluir as editoras que não publicaram livros.
DELETE FROM EDITORA
WHERE codigo NOT IN (
    SELECT DISTINCT editora_codigo FROM LIVRO WHERE editora_codigo IS NOT NULL
);