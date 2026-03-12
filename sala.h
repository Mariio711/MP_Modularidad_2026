struct sala
{
    char nombre[20];
    char descripcion[50];
    bool abierta;
};

void abrirSala(sala &s) {s.abierta = true;}

void mochila(sala &s, objeto o)
{
    if (s.abierta)
    {
        std::cout << "Has guardado el objeto " << o.nombre << " en la sala " << s.nombre << std::endl;
    }
    else
    {
        
    }
}

