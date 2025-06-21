       let ultimoID = null;

        async function checarNovoUsuario() {
            try {
                const response = await fetch("../api/ultimo_usuario.txt?_=" + new Date().getTime()); // evitar cache
                if (!response.ok) throw new Error("Erro ao acessar último usuário.");
                
                const id = (await response.text()).trim();

                if (id && id !== ultimoID) {
                    ultimoID = id;
                    mostrarNome(id);
                }
            } catch (error) {
                console.error("Erro:", error);
            }
        }

        async function mostrarNome(id) {
            try {
                const response = await fetch("../api/consultar.php?id=" + id);
                const nome = await response.text();
                const nomeDiv = document.getElementById("nome");

                nomeDiv.innerText = nome;
                nomeDiv.style.opacity = 1;

                setTimeout(() => {
                    nomeDiv.style.opacity = 0;
                }, 5000);
                await fetch("../api/limpar_ultimo_usuario.php");
                ultimoID = null;
            } catch (err) {
                console.error("Erro ao obter nome:", err);
            }
        }

        setInterval(checarNovoUsuario, 1000);