# www - Contenido de Virtual Host 1 (VH1)

Este directorio contiene los archivos estáticos, páginas de error personalizadas, scripts CGI y recursos utilizados por el Virtual Host principal del proyecto **webserv**.

## Estructura de carpetas

- **index.html**: Página principal de VH1.
- **404.html, 400.html, ...**: Páginas de error personalizadas para distintos códigos HTTP.
- **cgi-bin/**: Scripts CGI en PHP y Python que pueden ser ejecutados desde el servidor.
- **files/**: Archivos de ejemplo para descarga y pruebas.
- **Uploads/**: Carpeta donde se almacenan los archivos subidos mediante el formulario de upload.
- **errors/**: Páginas de error adicionales.

## Diagrama de flujo de www

```text
                +-------------------+
                |   index.html      |
                +-------------------+
                          |
        +-----------------+-----------------+
        |         |         |         |      |
   about.html  files/   cgi-bin/  upload.html uploads.html
        |         |         |         |      |
        |         |         |         |      |
   [info]   [listado]  [scripts]  [form]  [subidos]
        |         |         |         |      |
        +---------+---------+---------+------+
                          |
                  errors/ (páginas de error)
```

## Uso

- Accede a `index.html` para ver la página principal del Virtual Host 1.
- Utiliza los enlaces de navegación para acceder a las distintas funcionalidades: ver archivos, subir archivos, ejecutar scripts CGI, etc.
- Las páginas de error se muestran automáticamente cuando ocurre un error HTTP correspondiente.

## Notas


- El directorio incluye un **diagrama de flujo** que ilustra la estructura y el flujo de navegación de las páginas y recursos de `www`. Este diagrama facilita la comprensión de la arquitectura y la interacción entre los distintos componentes del Virtual Host 1.

---

**webserv** - 42 Málaga (2025)
Autores: druiz-ca, rdel-olm, sternero
