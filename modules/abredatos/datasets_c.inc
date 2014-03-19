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

//IMPORTANTE: tambien hay que editar abajo, la URL de retorno del formulario luego del ingreso
$_FG['table']          = 'abredatos_datasets'; // nombre de la table mysql
$_FG['edittitle']      = '<h1>Modificar Dataset</h1>'; // título de la pantalla cuando estamos editando datos
$_FG['newregtitle']    = '<h1>Crear nuevo Dataset</h1>'; // título de la pantalla cuando ingresamos nuevo registro
$_FG['editbutton']     = 'Confirmar modificación'; // Texto del boton del formulario cuando estamos en modo edicion
$_FG['newregbutton']   = 'Crear Dataset';  // Texto del boton del formulario cuando estamos ingresando un nuevo registro



FG_form_start ('form1'); // así se empiezan todos los formularios

FG_form_text ('name', 'Nombre del Dataset:<br>(a incluir en metadatos) ', $_FG['updateinfo']['name'], 'required,minSize[4],maxsize[50]');

           $dbmslist = FG_mkselect ('abredatos_DBMSs', $_FG ['updateinfo']['DBMS']); 
            FG_form_select ('DBMS', 'Conexión DBMS:', $dbmslist);

FG_form_text ('refreshtime', 'Intervalo actualización (horas):', $_FG['updateinfo']['refreshtime'], 'required,custom[integer]');
FG_form_container ('', '', ' &nbsp; 1 día: 24 horas &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;<b>Tabla de referencia de períodos expresados en horas</b><br> &nbsp; 1 semana: 168 horas<br> &nbsp; 1 quincena: 360 horas<br> &nbsp; 1 mes: 720 horas<br> &nbsp; 1 trimestre: 2160 horas<br>');


FG_form_textarea ('description', 'Descripción:<br>(a incluir en metadatos) ', $_FG['updateinfo']['description'], 'required');
FG_form_text ('institution', 'Institución que publica:<br>(a incluir en metadatos) ', $_FG['updateinfo']['institution'], 'required,minSize[3],maxsize[100]');

            $licenselist = FG_mkselect ('abredatos_licenses', $_FG ['updateinfo']['license']); 
            FG_form_select ('license', 'Licencia con que se publica:<br>(a incluir en metadatos) ', $licenselist);
                        
FG_form_text ('category', 'Categoría de datos:<br>(a incluir en metadatos) ', $_FG['updateinfo']['category']);


FG_form_submit ('submit', '', $_FG['buttontext']);


if ($_FG['is_reception']){

    if ($_FG['is_update']){
        $retorno = FG_dbupdate ($_FG['table'], $_FG['form1']);
        if ($retorno==FALSE) FG_error ('No se realizó ninguna modificación de datos');
        else FG_ok ('Se modificó el registro', $_SESSION['pageback']);
    }
    else {
        $retorno = FG_dbinsert ($_FG['table'], $_FG['form1'] );
        if ($retorno==FALSE) FG_error ('No se pudo ingresar el registro');
        else FG_ok ('Se insertó nuevo registro', '/abredatos/datasets');
    }
}


