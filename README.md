# Abredatos [DESCONTINUADO]
      __    ___   ___   ____  ___    __   _____  ___   __  
     / /\  | |_) | |_) | |_  | | \  / /\   | |  / / \ ( (` 
    /_/--\ |_|_) |_| \ |_|__ |_|_/ /_/--\  |_|  \_\_/ _)_) 
            
              Basado en la plataforma Free-gov (http://free-gov.org)

  #
  #  ESTE INSTRUCTIVO HA SIDO APORTADO POR EL MUNICIPIO DE MALDONADO
  #  http://www.municipiomaldonado.gub.uy/abredatos
  #
  #  Programador: Iris Montes de Oca (iris@municipiomaldonado.gub.uy)
  #               con apoyo de las comunidades de Software Libre
  #

  #  Versión del manual: 1.0 (16/5/2013) 
    
    
    SISTEMA "ABREDATOS" 

    CONTENIDO DEL MANUAL

      1) Requisitos del Sistema
      2) Precauciones de Seguridad
      3) Instalación
         3.1) Base de datos
         3.2) Configuración del archivo .configuration
         3.3) Personalización de imágenes y logos
         3.4) php.ini personalizado
         3.5) Tiempo límite de ejecución de scripts en PHP
      4) Creación inicial de usuarios y passwords
      5) Instalación como módulo en una plataforma Free-gov preexistente
         5.1) Copia del módulo
         5.2) Archivo de aterrizaje
         5.3) Creación del grupo y los permisos ACL
         5.4) El concepto de módulo en el contexto de una plataforma modular
      6) Fundamentos de uso del sistema
         6.1) CronJob y el script "run"
         6.2) MENU Conexiones DBMS
         6.3) MENU Tipos de Licencias
         6.4) MENU Administrar Datasets
         6.5) MENU  Campos de datos
         6.6) Datasets generados y publicación final
      7) Registros de actividad (logfiles)  
      8) Licencia del Software
      9) Por qué se eligió PHP como lenguaje para el desarrollo de este sistema


----------------------------------------------------------------------------------



1) REQUISITOS DEL SISTEMA

Para instalar 'ABREDATOS' es necesario contar con:
 - Cualquier sistema operativo para servidores (Linux, FreeBSD, Solaris, etc.)
 - Servidor Apache configurado con mod_rewrite y para usar archivos .htaccess
 - PHP version 5.2 o posterior con extensiones mysqli y gdlib
 - MySQL 5 o posterior
 - Un subdominio disponible en exclusividad para la instalación
 - Se recomienda disponer de la herramienta phpMyAdmin

Tenga presente que la instalación de la plataforma Free-gov modifica profundamente
el funcionamiento del servidor Apache en su subdominio. Por tanto es imposible 
hacer que este sistema coexista con alguna página web normal poniéndolo dentro de 
un directorio. Se debe disponer de un subdominio o dominio virtual con una 
estructura propia de directorios:

      http://www.sitioweb.gov/abredatos  >>  Incorrecto (da errores graves)
      http://abredatos.sitioweb.gov      >>  Correcto

PHP puede funcionar enlazado al servidor web Apache mediante mod_php, aunque se
recomienda la interfaz 'fastcgi', de mucho mejor performance.

No es necesario instalar previamente la plataforma de Gobierno Electrónico
Free-gov, ya que la misma está incluída y preconfigurada en esta distribución del
software. Si ya se dispone de una plataforma Free-gov, se puede agregar el módulo
'ABREDATOS' siguiendo las indicaciones del punto 5 en este mismo manual.

Como última precaución es oportuno aclarar que el proyecto contiene varios 
archivos ocultos (que comienzan con el caracter '.'). Muchos programas de FTP no
pueden ver o copiar estos archivos a menos que se les active la opción "mostrar
archivos ocultos".



2) PRECAUCIONES DE SEGURIDAD

Si sólo va a probar este software, cualquier instalación LAMP o WAMP moderna es
suficiente. Puede instalar fácilmente todo el software necesario desde
un paquete como XAMPP (http://sourceforge.net/projects/xampp/), que preinstala
Apache, Mysql, PHP, etc. de forma unificada y sin esfuerzo.
Pero una implementación de Gobierno Electrónico seria requiere un cortafuegos,
una auditoría de seguridad permanente con honeypots y detección de intrusiones, 
una política de respaldos diarios, de replicación de bases de datos, etc.
La plataforma de gobierno electrónico 'Free-gov' sobre la que se basa este sistema
es totalmente segura en la medida que sea manejada por administradores de sistemas
competentes y conscientes de que deben complementar toda instalación con las
diferentes herramientas de seguridad y respaldos disponibles para su sistema
operativo.
Como dice la documentación de 'Free-gov': "la seguridad de una implementación de
gobierno electrónico es directamente proporcional a la solidez profesional de
su administrador de sistemas"



3) INSTALACION

3.1 - Base de datos - Es necesario crear una serie de tablas en una base de datos 
MySQL. Estas tablas contienen la estructura ACL (permisos de acceso y usuarios),
así como las definiciones del módulo 'ABREDATOS'.
Para automatizar la creación inicial de las tablas, se suministra un archivo de
nombre 'abredatos.sql' en la raíz del proyecto.
Use el archivo 'abredatos.sql' desde su herramienta de gestión de 
MySQL (phpMyAdmin por ejemplo), ejecute las instrucciones SQL del archivo y se
crearán automáticamente las estructuras de datos necesarias, además de ciertas
configuraciones iniciales preestablecidas.


3.2 - Configuración del archivo .configuration - Este es el archivo principal de 
configuraión del sistema, y se encuentra en la carpeta free-gov-core. Si está 
en una plataforma UNIX (como Linux o FreeBSD) tenga presente que es un archivo 
oculto, y  configure su gestor de archivos y su cliente FTP para mostrar archivos
ocultos. Dentro de .configuration usted deberá configurar la URI del servidor 
MySQL (si el MySQL está en el mismo servidor web, ponga "loclhost", en caso 
contrario ponga el nombre o dirección IP del servidor de bases de datos). También
deberá poner el nombre de la base de datos a usar, el nombre de usuario y password 
de MySQL. Dentro de '.configuration' se puede configurar el texto que se verá en 
el título y en  el pie de cada página. Por último, la configuración de correo 
electrónico no es requerida en la instalación de 'ABREDATOS'


3.3 - Personalización de imágenes y logos - En la carpeta 'http-root/images' hay 
una imagen de nombre 'topbanner-trans.png' que es la que aparece en la portada del
Panl de Administración. Puede ser sustituída por otra imagen PNG de las mismas
dimensiones y con el mismo nombre.


3.4 - php.ini personalizado - La plataforma 'Free-gov' usa una configuración de 
PHP especial y optimizada (aunque no es un requerimiento forzoso). Si usted tiene
la posibilidad de manipular el php.ini global del servidor, use el archivo 
'php.ini' que se suministra dentro de la carpeta 'cgi-bin' del proyecto. Si no 
puede cambiar la configuración global de PHP, entonces siga las instrucciones del 
archivo README.txt suministrado en la carpeta 'cgi-bin'. Luego descomente las 
siguientes líneas, que son las primeras instrucciones del archivo .htaccess en la 
raíz de la instalación ("descomentar" o "quitar el comentario" es borrar el 
caracter # que precede la línea):

    #Options +ExecCGI
    #AddHandler php5-cgi .php
    #Action php-cgi /cgi-bin/php-wrapper.fcgi
    #Action php5-cgi /cgi-bin/php-wrapper.fcgi
    
La configuración del php.ini personalizado indicada en este paso no es forzosa, 
pero es clave para un uso más profesional de la plataforma de Gobierno Electrónico 
Free-gov (hay sistemas que en cada petición al front-controller establecen 
variables como zona horaria, nombre de las cookies por defecto, etc. El proyecto
Free-gov entiende que estos valores se deberían establecer sólo una vez durante
la instalación, aligerando el trabajo de CPU de cada petición, lo cual es muy
importante en servidores sujetos a mucha carga).

3.5 - Tiempo límite de ejecución de scripts en PHP - Por razones de seguridad, PHP
establece un tiempo máximo de ejecución para cada uno de los scripts en una insta-
lación determinada. De hecho, cada script tiene límites de consumo de memoria, de 
tiempo de ejecución, de cantidad de datos a recibir, etc, siendo todos estos valores
configurables desde el archivo php.ini mencionado en el apartado 3.4.
"Abredatos" tiene un script scheduler, de nombre "run", que se describe en el apartado
6.1 del presente manual. El mencionado script tiene realiza un trabajo potencialmente
muy intensivo (extraer los datos de varias tablas de bases de datos, para luego
archivarlos en formato .ZIP).
Por tanto, se debe configurar PHP para aumentar los recursos asignados a cada script,
en particular el tiempo de ejecución. Se debe establecer en php.ini:

     max_execution_time 120
     
que implica 120 segundos de tiempo de ejecución para los scripts. El administrador
del sistema debe hacer un seguimiento para encontrar el valor más apropiado según
el tamaño de los datasets a procesar, y el tiempo que el script "run" vaya a consumir.



4) CREACION INICIAL DE USUARIOS Y PASSWORDS

Los usuarios (funcionarios que tendrán acceso al sistema para administrar la
liberación de datos) se crean en la base de datos, en la tabla 'acl_users'.
Existe un  usuario inicial, de nombre 'usuarioinicial' y cuyo password es 
'cambiarurgente'. Este usuario fue creado en la línea 161 del archivo 
'abredatos.sql':

INSERT INTO `acl_users` (`id`, `username`, `cryptpass`, `realname`) VALUES
(1, 'usuarioinicial', '7e2a36a3697c83544ce49c35bb5c7bfe8ec50fc6', 'Usuario');

Como se puede ver, en la base de datos no se guardan los passwords, sino una firma
hash (MD5 + SHA2) del mismo, que por razones de seguridad es irreversible.
Al crear un usuario nuevo, se hace desde el administrador de la base de datos (que
puede ser phpMyAdmin, por ejemplo). A cada usuario que se ingrese, se le puede 
poner en el campo de password la cadena 7e2a36a3697c83544ce49c35bb5c7bfe8ec50fc6 
entonces ese usuario tendrá como password la cadena 'cambiarurgente'. El usuario 
deberá ingresar a su cuenta inmediatamente y cambiar el password por uno de su
preferencia, el que a su vez se guardará encriptado. Si un usuario olvida su 
password, el administrador lo podrá resetear volviendo a poner la cadena 
7e2a36a3697c83544ce49c35bb5c7bfe8ec50fc6 para que el usuario acceda por única vez
con el password 'cambiarurgente'.

Luego de creados cada usuario, es necesario manipular una segunda tabla del ACL 
(Access Control List) para hacer que estos usuarios pertenezcan al grupo 
'abredatos_admin'. Esto se hace en la tabla 'acl_users2groups'. Cada usuario 
-una vez ingresado a la tabla 'acl_users'- tiene un número de ID autoincremental 
asociado. En la tabla 'acl_users2groups' simplemente hay dos campos ('user' y 
'group'), y la llenamos poniendo entradas con el ID de cada usuario, y la cadena 
de grupo 'abredatos_admin'.  Para ilustrar lo explicado, abajo se muestra la 
línea del archivo 'abredatos.sql' que establece los permisos del usuario 
'usuarioinicial' (cuyo id es '1'):

  INSERT INTO `acl_users2groups` (`user`, `group`) VALUES
  (1, 'abredatos_admin');

Si creamos un usuario pero olvidamos darle pertenencia por lo menos a un grupo,
cuando este usuario ingrese al sistema verá un mensaje de error indicando que
no pertenece a ningún grupo y que no tiene permisos para nada (Free-gov usa una
política de seguridad de restricción por defecto apta para Gobierno Electrónico).
  
  
  
5) INSTALACION COMO MODULO EN UNA PLATAFORMA FREE-GOV PREEXISTENTE 
 
Si su organismo ya dispone de una instalación de la plataforma de Gobierno 
Electrónico Free-gov, entonces considere integrar el Sistema 'ABREDATOS'
como módulo de su instalación existente.
De esa forma, los usuarios de 'ABREDATOS' verán aparecer los comandos
de este software en el menú de su pantalla habitual de Free-gov, y a la vez éste
seguirá inaccesible para los usuarios que no hayan sido explícitamente agregados
al grupo de administradores de 'ABREDATOS'.

5.1 - Copia del módulo - en la carpeta 'modules' de su instalación existente de
Free-gov copie la carpeta 'abredatos' que se halla dentro de la carpeta 'modules'
de esta distribución.

5.2 - Archivo de aterrizaje - Para aquellos funcionarios que tengan acceso a otras 
funciones de su instalación Free-gov, el funcionamiento del sistema no presentará
cambios. Pero los funcionarios que sólo pertenezcan al grupo 'abredatos_admin'
necesitarán una pantalla "de aterrizaje" donde ingresar cuando entren al sistema.
El aterrizaje de 'ABREDATOS' es el archivo 'abredatos_admin.inc' que 
se halla dentro de las carpetas 'modules/main' Debe copiarlo en la ruta 
'modules/main' de su instalación de Free-gov existente.

5.3 - Creación del grupo y los permisos ACL - Desde el gestor de MySQL (phpMyAdmin)
cree el grupo 'abredatos_admin' en la tabla de grupos 'acl_groups':

  INSERT INTO `acl_groups` (`name`, `description`) VALUES
  ('abredatos_admin', 'manage abredatos');

Ahora debe crear el "mapa" que vincula al grupo con las diferentes operaciones 
permitidas, así como los elementos del menú que se crearán cuando corresponda.
Esto se realiza en la tabla 'acl_groups2res' que mapea los grupos a los recursos a
ser accesados, agregando las reglas para el grupo 'abredatos_admin'. Ejecute la 
siguiente instrucción SQL:
    
   INSERT INTO `acl_groups2res` (`group`, `module`, `operation`, 
   `negative`, `menu_group`, `menu_caption`) VALUES
   ('abredatos_admin', 'abredatos', 'index', 
     0, NULL, NULL),
   ('abredatos_admin', 'abredatos', 'DBMSs', 
     0, 'Administración de ABREDATOS', 'Conexiones DBMS'),
   ('abredatos_admin', 'abredatos', 'DBMSs_c', 
     0, NULL, NULL),
   ('abredatos_admin', 'abredatos', 'DBMSs_f', 
     0, NULL, NULL),
   ('abredatos_admin', 'abredatos', 'DBMSs_d', 
     0, NULL, NULL),
   ('abredatos_admin', 'abredatos', 'licenses', 
     0, 'Administración de ABREDATOS', 'Tipos de Licencias'),
   ('abredatos_admin', 'abredatos', 'licenses_c', 
     0, NULL, NULL),
   ('abredatos_admin', 'abredatos', 'licenses_d', 
     0, NULL, NULL),
   ('abredatos_admin', 'abredatos', 'datasets', 
     0, 'Administración de ABREDATOS', 'Administrar Datasets'),
   ('abredatos_admin', 'abredatos', 'datasets_c', 
     0, NULL, NULL),
   ('abredatos_admin', 'abredatos', 'datasets_f', 
     0, NULL, NULL),
   ('abredatos_admin', 'abredatos', 'datasets_d', 
     0, NULL, NULL),
   ('abredatos_admin', 'abredatos', 'campos', 
     0, 'Administración de ABREDATOS', 'Campos de datos'),
   ('abredatos_admin', 'abredatos', 'campos_c', 
     0, NULL, NULL),
   ('abredatos_admin', 'abredatos', 'campos_d', 
     0, NULL, NULL); 
    

Por último agregue los usuarios que corresponda al grupo 'abredatos_admin', 
de esta forma no sólo tendrán acceso al módulo 'ABREDATOS' sino que
además aparecerán los enlaces a las diferentes herramientas en el menú del
sistema del usuario. Un ejemplo de cómo agregar los usuarios con IDs 1, 5 y 100:

   INSERT INTO `acl_users2groups` (`user`, `group`) VALUES
   (1, 'abredatos_admin'),
   (5, 'abredatos_admin'),
   (100, 'abredatos_admin');

5.4 - El concepto de módulo en el contexto de una plataforma modular - Free-gov 
fue concebido para permitir que en una misma instalación coexistan una cantidad 
de módulos diversos, permitiendo a cada usuario ver sólo aquellos que 
corresponden a su tarea, y simplificando la tarea de usuarios que requieren el
uso de varias herramientas al centralizarlas todas bajo un mismo proceso de login.
En la URI de un usuario logueado en panel de control podemos ver:
    https://www.sitio.gov/MODULO/OPERACION/PARAMETRO1/PARAMETRO2/PARAMETROn

En nuestro caso MODULO es 'abredatos', mientras OPERACION puede ser por ejemplo 
'datasets_c', que es la pantalla desde donde se da de alta (create) un dataset.    



6) FUNDAMENTOS DE USO DEL SISTEMA

'ABREDATOS' es un sistema con un subsistema de acceso privado (donde los funcionarios 
crean, mantienen y consultan las conexiones a los servidores de bases de datos, los
datasets y sus metadatos, las licencias de uso de los datos abiertos, y los campos
de datos que integrarán el dataset desde las diferentes tablas SQL.

6.1 - CronJob y el script "run" - Un CronJob establecido para una periodicidad de 10 
minutos llama vía "wget" a un script PHP de nombre "run" localizado en la raíz del 
http-root de la instalación. EL script "run" debe ser invocado mediante un a petición 
HTTP GET que incluya un parámetro de nombre "secret", que debe contener la cadena
definida como ABREDATOS_SECRET en el archivo de configuración localizado en la carpeta
"free-gov-core/.configuration". Esto es para reducir las interferencias que se pudieran
producir por invocaciones espúreas al script "run".

Un ejemplo de crontab para este trabajo sería:
 
    */10 * * * * wget -O /dev/null http://datos.dominio.gov/run?secret=XXXXXX

6.2 - MENU Conexiones DBMS - Administra las conexiones a bases de datos. Para cada 
conexión se especifica la URI del servidor, el tipo de servidor SQL (admite 12 tipos, 
entre ellos MySQL, Oracle, IBM DB2, Informix, etc.), el puerto TCP/IP de escucha del 
servidor, el nombre de usuario a utilizar y su password. Es posible que varios datasets 
usen la misma configuración de conexión, por eso las conexiones se gestionan 
independientemente de los datasets.

6.3 - MENU Tipos de Licencias - Administra las licencias que se pueden aplicar a los 
datos a liberar. En principio y por defecto se incluyen cuatro licencias populares: 
GNU GPL Version 3, Creative Commons 3.0, Open Database License (ODbL) y OpenContent 
License (OPL). Desde esta sección el administrador tiene la libertad de modificar las 
licencias, eliminarlas, o incorporar otras nuevas.

6.4 - MENU Administrar Datasets - Antes de crear un dataset, se debe crear la conexión. 
Los datasets incluyen un nombre, una conexión (gestionada desde el menú 1: Conexiones 
DBMS), así como una detallada descripción, una licencia (administrada en 2: Tipos de 
licencia) y demás información necesaria para elaborar los meteadtos. Los campos de datos 
no se gestionan desde esta herramienta, sino de la herramienta 4 (Campos de datos). 

6.5 - MENU  Campos de datos - Desde aquí se administran los campos de datos integrarán 
los datasets. Se eligen los campos desde las diferentes tablas SQL, se omiten los campos 
de datos personales. Para cada tabla involucrada se creará un archivo CSV dentro del 
archivo ZIP del dataset. Se debe especificar (además del dataset al que se integrará cada 
campo) el nombre de la tabla SQL y el nombre del campo en la tabla. Dentro del dataset, 
el nombre del campo puede ser diferente, y éste nombre se especifica desde aquí.

6.6 - Datasets generados y publicación final - Los datasets generados se guardan en la
carpeta "data" dentro de la raíz del http-root de la instalación. En esta carpeta se
guardan los archivos .csv generados para cada tabla de cada dataset. También aquí se guardan
los archivos de metadatos, y finalmente los archivos .zip conteniendo los datos finales.
Para publicar los datos, basta con poner links en la web pública, enlazando a los archivos
de datos alojados en esta carpeta de la instalación de "abredatos". Los administradores
avanzados podrán implementar otros medios de publicación, como copiado, transferencia SCP,
FTP, o sincronización por "rsync", dependiendo de la topología de sus sistemas.



7) REGISTROS DE ACTIVIDAD (LOGFILES)

Free-gov guarda los registros de actividad en la tabla 'log' de la base de datos.
Allí registra toda la actividad que se realiza en el sistema: ingreso de usuarios,
cierres de sesión, errores, intentos de ataques, etc. Para cada registro guarda
día y hora detallada, características de la máquina con la que se accede, datos
del uso de un posible servidor proxy (una técnica muy usada por atacantes), etc.
En el caso de ataques, el sistema encripta la cadena usada por el atacante y la
guarda en el registro, junto a la dirección IP del origen del ataque.

Con toda esa información a almacenar, la tabla 'log' puede crecer desmedidamente,
por lo que se recomenda pasar periódicamente los datos a un soporte paralelo para
fines de archivo, y vaciar la tabla para mantener el servidor SQL más libre. 



8) LICENCIA DEL SOFTWARE

Este software se distribuye bajo la misma licencia de Software Libre que utiliza 
la Plataforma de Gobierno Electrónico 'Free-gov' sobre la que fue desarrollado.
Este software se puede descargar, estudiar, modificar, instalar en cuantas PCs se
desee, se puede copiar, se puede dar a terceros con total libertad... la única
restricción que impone la licencia es que cuando Ud. copie el software y se lo
de a un tercero, lo haga acompañado del código fuente del programa, y con las
mismas libertades con que Ud. lo recibió (y bajo la misma licencia).
La licencia es AGPL versión 3 (Affero General Public License), creada por la Free 
Software Foundation y reconocida por OSI (Open Source Initiative).
Una copia en inglés de la licencia acompaña al proyecto en el archivo license.txt
La licencia original en inglés es la que tiene valor legal en todo el mundo, y se
aplica de acuerdo al Derecho Internacional y los tratados internacionales sobre 
Derechos de Autor.

Puede leer más acerca de esta licencia en:
    http://es.wikipedia.org/wiki/GNU_Affero_General_Public_License

Puede acceder al texto oficial completo de la licencia AGPL en:
    http://www.gnu.org/licenses/agpl.html

Al momento de escribir este documento lamentablemente no existían traducciones al
español del texto de la licencia AGPL.



9) POR QUE SE ELIGIO PHP COMO LENGUAJE PARA EL DESARROLLO DE ESTE SISTEMA

Compartimos las mismas razones que el proyecto Free-gov enumera en su sitio:

- PHP es Software Libre, y además de ahorrar costos de licencias, su modelo de
desarrollo Open Source (con decenas de miles de programadores estudiando,
analizando y mejorando el producto) ha hecho de PHP la plataforma de desarrollo
para programación web más sólida y completa del mercado, superando con creces
a cualquier producto comercial.
- PHP actúa como un lenguaje interpretado, y sin embargo es posible compilar
los scripts para mejorar la velocidad de ejecución (ejemplo: Facebook)
- PHP es el más popular de los lenguajes de programación Server-Side, por lo
tanto es más sencillo hallar programadores calificados, colaboradores, etc. 
- PHP es multiplataforma y puede ser usado con cualquier sistema operativo, y
con cualquier servidor web. No estamos forzados a usar un sistema en particular
- PHP es ampliamente usado en las empresas de hosting comercial, por tanto un
sistema en PHP puede ser fácilmente migrado a cualquier servidor externo, aún
los de más bajo costo.
- PHP (cuando está debidamente instalado y configurado) es una plataforma de
extrema seguridad, perfectamente apta para Gobierno Electrónico, tal como lo
demuestra el proyecto Free-gov.
- PHP soporta programación de alto y bajo nivel (tan bajo como sockets TCP/IP)
- PHP está pre-empaquetado con Apache y MySQL por defecto en la mayoría de las 
distribuciones Linux, así como en FreeBSD, OpenBSD, Solaris, etc.
- PHP soporta tanto Programación Orientata a Obejtos (OOP) como Programación
Procedural Estructurada (esta última es la preferida por Free-gov).

PHP es la tecnología elegida por muchos de los sitios web más grandes del mundo:
Yahoo, Wikipedia, Facebook, Youtube, Flickr, Digg, y partes de Google.
PHP también es usado por aproximadamente el 75% de todos los servidores a nivel
mundial.



