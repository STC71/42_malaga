# www2 - Contenido de Virtual Host 2 (VH2)

Este directorio contiene los archivos estáticos, páginas de error personalizadas, scripts CGI y recursos utilizados por el Virtual Host secundario del proyecto **webserv**.

## Estructura de carpetas

- **index.html**: Página principal de VH2.
- **404.html, 400.html, ...**: Páginas de error personalizadas para distintos códigos HTTP.
- **cgi-bin/**: Scripts CGI en PHP y Python que pueden ser ejecutados desde el servidor.
- **files/**: Archivos de ejemplo para descarga y pruebas en VH2.
- **Uploads/**: Carpeta donde se almacenan los archivos subidos mediante el formulario de upload en VH2.
- **errors/**: Páginas de error adicionales.

## Diagrama de flujo de www2

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

- Accede a `index.html` para ver la página principal del Virtual Host 2.
- Utiliza los enlaces de navegación para acceder a las distintas funcionalidades: ver archivos, subir archivos, ejecutar scripts CGI, etc.
- Las páginas de error se muestran automáticamente cuando ocurre un error HTTP correspondiente.

## Notas

- Este directorio está pensado para ser servido como raíz del Virtual Host 2 en el servidor webserv.
- Los scripts en `cgi-bin/` deben tener permisos de ejecución.
- Los archivos subidos por los usuarios se almacenan en `Uploads/`.
- El diseño y la navegación están adaptados para una demo profesional y coherente, con diferencias respecto a VH1 para mostrar la funcionalidad multi-host.

---

**webserv** - 42 Málaga (2025)
Autores: druiz-ca, rdel-olm, sternero
