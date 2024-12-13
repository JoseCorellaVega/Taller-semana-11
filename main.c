#include <stdio.h>
    #include <string.h>

    #define MAX_LIBROS 20

    struct Libro {
        int id;
        char titulo[100];
        char autor[50];
        int publicado;
        char estado[20]; // "Disponible" o "Prestado"
    };


    struct Libro biblioteca[MAX_LIBROS];
    int totalLibros = 0;

    // Prototipos de funciones
    void registrarLibro();
    void mostrarLibros();
    void buscarLibro();
    void actualizarEstadoLibro();
    void eliminarLibro();
    int validarIDUnico(int id);

    int main() {
        int opcion;
        do {
            printf("\n--- Sistema de Gestion de Biblioteca ---\n");
            printf("1. Registrar libro\n");
            printf("2. Mostrar lista de libros\n");
            printf("3. Buscar libro (por titulo o ID)\n");
            printf("4. Estado de un libro\n");
            printf("5. Eliminar libro\n");
            printf("6. Salir\n");
            printf("Ingrese una opcion: ");
            scanf("%d", &opcion);
            getchar(); // Limpiar buffer

            switch (opcion) {
                case 1: registrarLibro(); break;
                case 2: mostrarLibros(); break;
                case 3: buscarLibro(); break;
                case 4: actualizarEstadoLibro(); break;
                case 5: eliminarLibro(); break;
                case 6: printf("Salir\n"); break;
                default: printf("Opcion no valida. Intente de nuevo.\n");
            }
        } while (opcion != 6);

        return 0;
    }

    void registrarLibro() {
        if (totalLibros >= MAX_LIBROS) {
            printf("No se pueden registrar mas libros. Limite alcanzado.\n");
            return;
        }

        struct Libro nuevoLibro;
        printf("Ingrese el ID del libro: ");
        scanf("%d", &nuevoLibro.id);
        getchar();

        if (!validarIDUnico(nuevoLibro.id)) {
            printf("El ID ya existe. Intente con otro.\n");
            return;
        }

        printf("Ingrese el titulo del libro: ");
        fgets(nuevoLibro.titulo, 100, stdin);
        nuevoLibro.titulo[strcspn(nuevoLibro.titulo, "\n")] = '\0';

        printf("Ingrese el autor del libro: ");
        fgets(nuevoLibro.autor, 50, stdin);
        nuevoLibro.autor[strcspn(nuevoLibro.autor, "\n")] = '\0';

        printf("Ingrese el ano de publicacion: ");
        scanf("%d", &nuevoLibro.anioPublicacion);
        getchar();

        strcpy(nuevoLibro.estado, "Disponible");
        biblioteca[totalLibros] = nuevoLibro;
        totalLibros++;

        printf("Libro registrado exitosamente.\n");
    }

    void mostrarLibros() {
        if (totalLibros == 0) {
            printf("No hay libros registrados.\n");
            return;
        }

        printf("\nLista de libros:\n");
        printf("ID | Titulo | Autor | Ano | Estado\n");
        printf("---------------------------------------------\n");

        for (int i = 0; i < totalLibros; i++) {
            printf("%d | %s | %s | %d | %s\n", 
                biblioteca[i].id, 
                biblioteca[i].titulo, 
                biblioteca[i].autor, 
                biblioteca[i].anioPublicacion, 
                biblioteca[i].estado);
        }
    }

    void buscarLibro() {
        char criterio[100];
        printf("Ingrese el titulo o ID del libro a buscar: ");
        fgets(criterio, 100, stdin);
        criterio[strcspn(criterio, "\n")] = '\0';

        for (int i = 0; i < totalLibros; i++) {
            if (strcmp(biblioteca[i].titulo, criterio) == 0 || strcmp(criterio, "") != 0 && biblioteca[i].id == atoi(criterio)) {
                printf("\nLibro encontrado:\n");
                printf("ID: %d\nTitulo: %s\nAutor: %s\nAnio: %d\nEstado: %s\n", 
                    biblioteca[i].id, 
                    biblioteca[i].titulo, 
                    biblioteca[i].autor, 
                    biblioteca[i].anioPublicacion, 
                    biblioteca[i].estado);
                return;
            }
        }
        printf("Libro no encontrado.\n");
    }

    void actualizarEstadoLibro() {
        int id;
        printf("Ingrese el ID del libro para cambiar su estado: ");
        scanf("%d", &id);
        getchar();

        for (int i = 0; i < totalLibros; i++) {
            if (biblioteca[i].id == id) {
                if (strcmp(biblioteca[i].estado, "Disponible") == 0) {
                    strcpy(biblioteca[i].estado, "Prestado");
                } else {
                    strcpy(biblioteca[i].estado, "Disponible");
                }
                printf("Estado actualizado exitosamente.\n");
                return;
            }
        }
        printf("Libro no encontrado.\n");
    }

    void eliminarLibro() {
        int id;
        printf("Ingrese el ID del libro a eliminar: ");
        scanf("%d", &id);
        getchar();

        for (int i = 0; i < totalLibros; i++) {
            if (biblioteca[i].id == id) {
                for (int j = i; j < totalLibros - 1; j++) {
                    biblioteca[j] = biblioteca[j + 1];
                }
                totalLibros--;
                printf("Libro eliminado exitosamente.\n");
                return;
            }
        }
        printf("Libro no encontrado.\n");
    }

    int validarIDUnico(int id) {
        for (int i = 0; i < totalLibros; i++) {
            if (biblioteca[i].id == id) {
                return 0; // El ID ya existe
            }
        }
        return 1; // El ID es unico
    }
