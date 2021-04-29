# Proyecto Sistemas Operativos 2

#### Grupo 30

|              Nombre               |  Carnet   |
| :-------------------------------: | :-------: |
|   Duglas Francisco Avila Torres   | 201314778 |
|    Luis Ruperto Salazar Orozco    | 201213181 |
| Diego Antonio Momotic Montesdeoca | 201318633 |



#### Prometheus y Grafana

Es un sistema de monitoreo de código abierto basado en métricas.  Recopila datos de servicios y hosts mediante el envío de solicitudes  HTTP en puntos finales de métricas. Luego, almacena los resultados en  una base de datos de series de tiempo y los pone a disposición para  análisis y alertas.

###### Instalación y configuración

1. Actualización de repositorios de Ubuntu

   ```bash
   sudo apt-get update
   ```

2. Agregando repositorio de Prometheus

   ```bash
   wget https://s3-eu-west-1.amazonaws.com/deb.robustperception.io/41EFC99D.gpg | apt-key add -
   ```

3. Instalando Prometheus

   ```bash
   sudo apt-get update
   
   sudo apt-get install prometheus prometheus-node-exporter prometheus-pushgateway prometheus-alertmanager -y
   
   sudo systemctl status prometheus
   ```

4. Habilitando puerto (reglas UFW)

   ```bash
   sudo ufw status
   
   sudo ufw allow 9090
   ```

5. Acceso al panel web

   `http://localhost:9090 o http://IP_Address:9090`

   ![Panel principal](https://1.bp.blogspot.com/-GWcaP-XX1-Y/X-kLYj8f_2I/AAAAAAAAID4/S5RLpX3_83wZnc5B41BjcXe3cDflBnamgCLcBGAsYHQ/w640-h192/prometheus_2_techbeginner.PNG)

   

   Ejecutar instrucción **up** para obtener información del nodo en ejecución.

   ![Obteniendo información](https://1.bp.blogspot.com/-QeNSyoJbzPw/X-kLinCSpnI/AAAAAAAAID8/i8onrZLDVmYBsy8UAuqje-f2uXAWQm8lwCLcBGAsYHQ/w640-h210/prometheus_3_techbeginner.PNG) 

   

   En la pestaña **status/target** se podemos observar la información de los nodos.

   ![Información](https://1.bp.blogspot.com/-PB1NknHsjKU/X-kLo_M9diI/AAAAAAAAIEE/12xaRHx2QnoY-h6FMFTSp0GzavB_6oJ0gCLcBGAsYHQ/w640-h210/prometheus_4_techbeginner.PNG)

6. Descargando Grafana

   ```bash
   cd /tmp
   
   sudo wget https://dl.grafana.com/oss/release/grafana_5.4.3_amd64.deb
   ```

7. Instalando dependencias

   ```bash
   sudo apt-get install -y adduser libfontconfig
   ```

8. Instalando Grafana

   ```bash
   sudo dpkg -i grafana_5.4.3_amd64.deb
   ```

9. Habilitando servicio

   ```bash
   sudo systemctl enable grafana-server
   
   sudo systemctl start grafana-server
   
   sudo systemctl status grafana-server
   ```

10. Habilitando puertos (reglas UFW)

    ```bash
    sudo ufw status
    
    sudo ufw allow 3000
    ```

11. Configurando Grafana desde la interfaz gráfica, ingresar a: `http://localhost:3000 o http://IP_address:3000` con las crendenciales **admin/admin**

    ![Grafana login](https://1.bp.blogspot.com/-w32Pyn0uL14/X_icw53eS6I/AAAAAAAAIQs/3K_J7R23mBMJmd1zqkgeLseg1Nw5VPK1QCLcBGAsYHQ/w640-h326/grafana_1_techbeginner.PNG)

    

    Seleccionar la opción **Add data source**

    ![Agregando data source](https://1.bp.blogspot.com/-Rw0b6SxBLMw/X_ikc4BX6AI/AAAAAAAAIRw/oS1Oa-paJasFdJgBCNkG6ChTp4ChlCy9ACLcBGAsYHQ/w640-h312/MicrosoftTeams-image_techebginner.png)

    

    Seleccionamos **Prometheus**

    ![Prometheus data source](https://1.bp.blogspot.com/-OOQmS4DJFko/X_ij1_ynxEI/AAAAAAAAIRk/rVslTbgNm_w-kmd7atuU2l-w7fKPH7yqACLcBGAsYHQ/w640-h308/MicrosoftTeams-image%2B%252812%2529.png)

    

    Datos para la conexión con el servidor de **Prometheus**

    ![Conexión con Prometheus](https://1.bp.blogspot.com/-2HpKZdkESEQ/X_idAoy7XtI/AAAAAAAAIQ4/Va0Mxu0Mcqk4EvXdnTDtWk1RhKuscQtJwCLcBGAsYHQ/w610-h640/grafana_5_techbeginner.PNG)

    

    Si todo salió bien debemos ver un mensaje como este

    ![Conexión realizada](https://1.bp.blogspot.com/-_u3blSqhzYU/X_idHd3XG_I/AAAAAAAAIRA/qfwJbhkp5bwuEjZytlMgXYgjfOkKZfWPACLcBGAsYHQ/w640-h222/grafana_6_techbginner.PNG)

    

12. Instalando dashboard

    Desde la sección de import buscar el dashboard con id **7039**

    ![Buscando dashboard](https://1.bp.blogspot.com/-DUHoD845u-k/X_idOCO-RwI/AAAAAAAAIRE/lZvPLJ8ghGQopdKopeb97S1ED8t9y2yigCLcBGAsYHQ/w640-h300/grafana_7_techbeginner.PNG)

    

    Al cargar el dashboard debemos seleccionar la opción de **Prometheus** nuevamente

    ![Prometheus](https://1.bp.blogspot.com/-Cc69duZlooY/X_idUtxQQqI/AAAAAAAAIRI/1aIqGPXGa348JhIkMUbcKec08WqIsyhPQCLcBGAsYHQ/w640-h308/grafana_8_techbeginner.PNG)

    

    Luego al importar finalmente podremos visualizar toda la información en el dashboard.

    ![Dashboard con información](https://1.bp.blogspot.com/-pOF6PjaCpGw/X_idez-StrI/AAAAAAAAIRQ/j5LcgfwW9xk_zIojcYmfPSSHXWjz0NR7wCLcBGAsYHQ/w640-h312/grafana_9_techbeginner.PNG)



#### Kubernetes

1. Creación de clúster de Kubernetes desde Google Cloud Platform

   ![Creación clúster](https://i.ibb.co/sK5Y4dM/Captura.png)

   

2. Creación de base de datos en Mongo Atlas

   ![Base de datos](https://i.ibb.co/b2MZVw9/Captura.png)

   

3. Desarrollo de backend y frontend

   ![Desarrollo](https://i.ibb.co/tbr9mFy/Captura.png)

   

4. Dockerización de aplicaciones, para el **backend** se utilizó la imagen de **node** y para el **frontend** se utilizaron 2 imágenes la primera **node** para la construcción de la aplicación de **react** y la segunda imagen de **nginx** para servir la aplicación construida de **react**

   ![Dockerizacion](https://i.ibb.co/wsVpR5D/Captura.png)

   

5. Almacenamiento en Docker Hub (ambas imágenes fueron almacenadas aquí)

   ![Docker Hub](https://i.ibb.co/km0JyWN/Captura.png)

   

6. Creación de Deployments, de acuerdo con las especificaciones del enunciado, varia el número de replicas de cada pod, la imagen y las variables de entorno.

   ![Deployments](https://i.ibb.co/WszrmFr/Captura.png)

   

7. Creación de Services tipo LoadBalancer para exponer las aplicaciones desarrolladas

   ![Services](https://i.ibb.co/Ld2b7MG/Captura.png)

   

8. Deployments, pods y servicios corriendo en el clúster

   ![Objetos](https://i.ibb.co/zS8TRxF/Captura.png)

#### Referencias

- [https://geekflare.com/es/prometheus-grafana-intro/](https://geekflare.com/es/prometheus-grafana-intro/)
- [https://www.techbeginner.in/2020/12/how-to-install-prometheus-on-ubuntu.html](https://www.techbeginner.in/2020/12/how-to-install-prometheus-on-ubuntu.html)

