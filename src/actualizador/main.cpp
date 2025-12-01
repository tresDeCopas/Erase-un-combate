#include <iostream>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include <fstream>
#include <filesystem>
#include <zip.h>
#include <unistd.h>


// Obtiene de GitHub el código de la última versión del juego (por ejemplo,
// un código podría ser v1.0.1)
cpr::Response obtenerCodigoVersion(){
    return cpr::Get(cpr::Url{"https://api.github.com/repos/MascaChapas27/Erase-un-combate/releases/latest"});
}

// Pide al usuario que indique si quiere volver a intentar actualizar en
// caso de que algo no vaya bien
bool reintentarActualizacion(long codigoErroneo){
    std::cout << "Error: la peticion ha devuelto un codigo " << codigoErroneo << ", por lo que no ha sido posible completar el proceso de actualizacion.\n";
    std::cout << "Quieres seguir intentando buscar actualizaciones? (S/N): ";
    char respuestaJugador;
    std::cin >> respuestaJugador;
    return respuestaJugador == 'S';
}

// Descarga el .zip de la nueva versión del juego
cpr::Response descargarActualizacion(nlohmann::json_abi_v3_12_0::json json){
    std::cout << "Descargando...\n";
    std::ofstream destinoDescarga("nueva-version.zip", std::ios::binary);
    return cpr::Download(destinoDescarga, cpr::Url(json["assets"][0]["browser_download_url"]));
}

// Borra los archivos correspondientes a la versión antigua (NO
// TOCA LOS ARCHIVOS DE GUARDADO, ESO ES SAGRADO)
void borrarArchivosViejos(std::filesystem::path base){

    for (const auto& entry : std::filesystem::directory_iterator(base)) {
        std::string nombre = entry.path().filename().string();

        // Excepciones: no borrar estos archivos/carpeta
        if (nombre == "EraseUnActualizador.exe" ||
            nombre == "nueva-version.zip" ||
            nombre == "guardado" ||
            nombre == "add-compressed-data.exe" ||
            nombre == "autoclose-archive.exe" ||
            nombre == "in-memory.exe" ||
            nombre == "zip_read_file_fuzzer.exe" ||
            nombre == "zip_read_fuzzer.exe" ||
            nombre == "zip_write_encrypt_aes256_file_fuzzer.exe" ||
            nombre == "zip_write_encrypt_pkware_file_fuzzer.exe" ||
            nombre == "zipcmp.exe" ||
            nombre == "zipmerge.exe" ||
            nombre == "ziptool.exe" ||
            nombre == "libzip.dll")
            continue;

        try {
            if (std::filesystem::is_directory(entry.path())) {
                std::cerr << "Entrando al directorio " << nombre << "\n";
                borrarArchivosViejos(entry.path());

                std::this_thread::sleep_for(std::chrono::milliseconds(1000));

                std::cerr << "Eliminando directorio " << nombre << "\n";
                std::filesystem::remove(entry.path());
            } else {
                std::cerr << "Eliminando archivo " << nombre << "\n";
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                std::filesystem::remove(entry.path());
            }
        } catch (const std::filesystem::filesystem_error& e) {
            std::cerr << "Error al eliminar " << nombre << ": " << e.what() << "\n";
        }
    }
}

// Obtiene el código de versión actual
std::string obtenerVersionActual(){
    std::ifstream ficheroVersion("version.txt");
    std::string versionActual;
    ficheroVersion >> versionActual;
    return versionActual;
}

// Extrae los archivos del .zip, actualizando el juego
void aplicarActualizacion(){
    int err = 0;
    zip_t* za = zip_open("nueva-version.zip", ZIP_RDONLY, &err);
    if (!za) {
        std::cerr << "No se pudo abrir el archivo ZIP.\n";
    }

    zip_int64_t num_entries = zip_get_num_entries(za, 0);
    for (zip_uint64_t i = 0; i < num_entries; ++i) {
        const char* name = zip_get_name(za, i, 0);
        if (!name) continue;

        std::string fullPath = "./" + std::string(name);

        // Manejar directorios
        if (name[strlen(name) - 1] == '/') {
            std::filesystem::create_directories(fullPath);
            continue;
        } else {
            std::filesystem::create_directories(std::filesystem::path(fullPath).parent_path());
        }

        zip_file_t* zf = zip_fopen_index(za, i, 0);
        if (!zf) {
            std::cerr << "No se pudo abrir el archivo dentro del zip: " << name << "\n";
            continue;
        }

        std::ofstream outFile(fullPath, std::ios::binary);
        char buffer[4096];
        zip_int64_t n;
        while ((n = zip_fread(zf, buffer, sizeof(buffer))) > 0) {
            outFile.write(buffer, n);
        }

        zip_fclose(zf);
        outFile.close();
        std::cout << "Extraído: " << name << "\n";
    }

    zip_close(za);

    std::filesystem::remove("nueva-version.zip");
}

int main(){

    // Esta es la respuesta obtenida por el servidor de GitHub
    cpr::Response respuestaHTTP;

    // Aquí se guarda una S si se quiere seguir buscando actualizaciones aunque no
    // haya funcionado a la primera. Depende de lo que responda el jugador
    bool seguirIntentando;

    // Aquí se guarda la versión actual del juego
    std::string versionActual;

    do
    {
        versionActual = obtenerVersionActual();

        std::cout << "##################################\n";
        std::cout << "Estas jugando a la version " << versionActual << ". Buscando actualizaciones...\n";
        respuestaHTTP = obtenerCodigoVersion();

        if (respuestaHTTP.status_code != 200) {
            seguirIntentando = reintentarActualizacion(respuestaHTTP.status_code);
        } else {
            nlohmann::json_abi_v3_12_0::json json = nlohmann::json::parse(respuestaHTTP.text);
            std::cout << "La version mas nueva del juego es la " << json["tag_name"] << ".\n";

            if(json["tag_name"] == versionActual){
                std::cout << "Estas jugando a la ultima version.\n";
                system("pause");
            } else {
                std::cout << "Estas jugando una version distinta. Quieres actualizar? (S/N)\n";
                char respuestaJugador;
                std::cin >> respuestaJugador;

                if(respuestaJugador == 'S'){
                    respuestaHTTP = descargarActualizacion(json);
                    if (respuestaHTTP.status_code != 200) {
                        seguirIntentando = reintentarActualizacion(respuestaHTTP.status_code);
                    }
                    // borrarArchivosViejos(std::filesystem::absolute("."));
                    aplicarActualizacion();
                }
            }
        }
    } while(respuestaHTTP.status_code != 200 && seguirIntentando);

    execl("EraseUnCombate.exe","EraseUnCombate.exe",nullptr);
    perror("Error al iniciar el juego");
}