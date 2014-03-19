<?php
    #         ____
    #        / __/________  ___        ____ _____ _   __
    #       / /_ / ___/ _ \/ _ \______/ __ `/ __ \ | / /
    #      / __// /  /  __/  __/_____/ /_/ / /_/ / |/ /
    #     /_/  /_/   \___/\___/      \__, /\____/|___/   > http://free-gov.org
    #                               /____/
    #
    #  This file is part of 'Free-gov' - http-root/badbrowser.php
    #
    #  Free-gov - e-government free software system
    #  Copyright (C) 2011 Iris Montes de Oca <http://www.irismontesdeoca.com>
    #  Copyright (C) 2011 Eduardo Glez <http://www.eduardoglez.com>
    #
    #  Free-gov is free software; you can redistribute it and/or modify
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
    #            Eduardo Glez <http://www.eduardoglez.com>
    #  Internet: http://free-gov.org
    #
    #  Registered in the United States Copyright Office on May 18, 2011
    #  Registration Number at the Library of the Congress of the USA: TXu001756584
    #


$_FG['render']['title'] = 'Free-gov Free e-Government Software';
$_FG['render']['footer'] = "Free-gov Free e-Government Software";

$_FG['render']['main'] = <<<EOF

<br><h1>Acceso bloqueado por razones de seguridad</h1>

<center>
<table width=800 cellpadding=20 cellspacing=20 border=0><tr>
<td width=250 align="center" valign="top"><img src="/images/no_ie.jpg" width=200 height=200></td>
<td valign="top" align="left">
<h2>Aviso Importante</h2>
No intente acceder a este sistema  usando su navegador <b>Internet Explorer</b>. Este navegador no cumple con los mínimos <a href="http://www.webstandards.org/">estándares de seguridad en la web</a>.<br>
Por favor use cualquier otro navegador que brinde un mínimo de seguridad:
<br>
<center>
<table width=400 cellpadding=0 cellspacing=0 border=0><tr><td align="left">
<ul>
<li>Mozilla firefox</li>
<li>Google chrome</li>
<li>Opera</li>
<li>Safari</li>
</ul>
</td></tr></table>
</center><br>
<h2>Más información sobre el tema</h2>

<center>
<table width=400 cellpadding=0 cellspacing=0 border=0><tr><td align="left">
<ul>
<li><a href="https://www.bsi.bund.de/cln_183/ContentBSI/presse/Pressemitteilungen/Sicherheitsluecke_IE_150110.html">Recomendaciones y Comunicado del Gobierno Alemán</a> (en alemán)</li>
<li><a href="http://www.danielclemente.com/navega/popup.html">Artículo ¿Aún usas Internet Explorer?<a> (en español)</li>
<li><a href="http://www.dailymail.co.uk/sciencetech/article-1244138/Internet-Explorer-Germany-warns-using-IE-Microsoft-admits-browser-weak-link-China-Google-hacks.html">Gobierno Francés recomienda no usar Internet Explorer</a> (en inglés)</li>
</ul>
</td></tr></table>
</center>

</td>
</tr></table></center>

EOF;


include ('template_nomenu.html');  
