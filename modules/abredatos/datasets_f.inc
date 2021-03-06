<?php
    #
    #   ABREDATOS - Software de extracción, anonimización y publicación 
    #               de Datos Abiertos - SOFTWARE PUBLICO URUGUAYO
    # 
    #  Creado en el Municipio de Maldonado (http://www.municipiomaldonado.gub.uy)
    #  por Iris Montes de Oca (http://www.irismontesdeoca.com)
    #  en la plataforma de Gobierno Electrónico Free-gov (http://free-gov.org)
    #    
    #  Este Software de distribuye bajo los términos de la Licencia AGPL 3
    #  El texto de la licencia AGPL se encuentra an el archivo 'license.txt'
    #  (en idioma inglés), en el mismo paquete de distribución de este software.
    #
    #  El cumpliminto internacional de la Licencia AGPL requiere la inclusión
    #  del siguiente bloque de licenciamiento en idioma inglés, en cada archivo:
    #
    #
    #  This file is part of 'ABREDATOS' 
    #
    #  ABREDATOS - Open Data extraction and publishing toolkit.
    #  Copyright (C) 2013 Iris Montes de Oca <http://www.irismontesdeoca.com>
    #  working with Municipio de Maldonado <http://www.municipiomaldonado.gub.uy>
    #
    #  ABREDATOS is free software; you can redistribute it and/or modify
    #  it under the terms of the GNU Affero General Public License as published
    #  by the Free Software Foundation; either version 3 of the License, or
    #  (at your option) any later version.
    #
    #  Free-gov is distributed in the hope that it will be useful,
    #  but WITHOUT ANY WARRANTY; without even the implied warranty of
    #  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    #  GNU Affero General Public License for more details.
    #
    #  You should have received a copy of the GNU Affero General Public License
    #  along with Free-gov: see the file 'license.txt'.  If not, write to
    #  the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
    #  Boston, MA 02111-1307, USA.
    #
    #   Authors: Iris Montes de Oca <http://www.irismontesdeoca.com>
    #  Internet: http://www.municipiomaldonado.gub.uy/abredatos
    #
    #  This software is built on top of free-gov platform (http://free-gov.org)
    #

echo <<<EOF
<h1> &nbsp;Detalles de Dataset</h1><br>
EOF;

$_FG['substitutions'] = array ('license'=>'abredatos_licenses',  'DBMS'=>'abredatos_DBMSs');

$fields = array ('name'=>'Nombre del Dataset:<br>(a incluir en metadatos) ', 'DBMS'=>'Conexión DBMS:', 'refreshtime'=>'Intervalo actualización (horas):',  'description'=>'Descripción:<br>(a incluir en metadatos) ', 'institution'=>'Institución que publica:<br>(a incluir en metadatos) ', 'license'=>'Licencia con que se publica:<br>(a incluir en metadatos) ', 'category'=>'Categoría de datos:<br>(a incluir en metadatos) ');

FG_details ('abredatos_datasets', $fields);
