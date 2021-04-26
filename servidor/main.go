package main

import (
	"fmt"
	"io/ioutil"
	"log"
	"net/http"
	"os"
	"os/exec"

	"github.com/rs/cors"
)

//Obtengo la informacion de la RAM
func getRAMInfo() string {
	filedata, err := ioutil.ReadFile("/proc/mem_grupo30")
	if err != nil {
		fmt.Println("Error al abrir mem_grupo30")
		return ""
	}
	return string(filedata)
}

//Obtengo la informacion del CPU desde el proc
func getCPUInfo() string {
	filedata, err := ioutil.ReadFile("/proc/cpu_grupo30")
	if err != nil {
		fmt.Println("Error al abrir cpu_grupo30")
		return ""
	}
	return string(filedata)
}

func killByPID(pid string) {
	output, err := exec.Command("kill", "-9", pid).CombinedOutput()
	if err != nil {
		log.Println(err.Error())
		os.Stderr.WriteString(err.Error())
	}
	fmt.Println(string(output))
}

func main() {
	//Servidor
	mux := http.NewServeMux()

	//Ruta que retorna JSON con la informacion de la RAM
	mux.HandleFunc("/ram", func(w http.ResponseWriter, r *http.Request) {
		w.Header().Set("Content-Type", "application/json")
		w.Write([]byte(getRAMInfo()))
	})

	//Ruta que retorna JSON con la informacion del CPU
	mux.HandleFunc("/cpu", func(w http.ResponseWriter, r *http.Request) {
		w.Header().Set("Content-Type", "application/json")
		w.Write([]byte(getCPUInfo()))
	})

	mux.HandleFunc("/process/kill", func(w http.ResponseWriter, r *http.Request) {
		w.Header().Set("Content-Type", "application/json")

		//r.RequestURI = /process/kill?pid=numero
		pid := r.RequestURI[18:]
		killByPID(pid)
		w.Write([]byte("{message:\"All done\"}"))
	})

	//Ruta que retorna index.html
	mux.Handle("/", http.FileServer(http.Dir("./public")))

	//Servidor iniciado
	handler := cors.Default().Handler(mux)
	log.Println("Serving golang server...")
	log.Fatal(http.ListenAndServe(":8000", handler))
}