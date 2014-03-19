#!/bin/bash

wget -O /dev/null http://datos.municipiomaldonado.gub.uy/run?secret=XXXXXX 

#
#  Este script de shell debe ser invocado por CRON cada una hora
#  Edite este archivo para adecuarlo a la URI de su instalación,
#  y usa la misma clave (ABREDATOS_SECRET) del archivo de confi-
#  guración free-gov-core/.configuration
#
#  INFORMACION SOBRE CRON:   http://es.wikipedia.org/wiki/Cron_%28Unix%29
#
#

