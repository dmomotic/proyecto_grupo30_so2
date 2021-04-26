
#include <linux/proc_fs.h>
#include <linux/hugetlb.h>
#include <linux/module.h> 

/* Obtiene el dato en kilobytes */
#define K(x) ((x) << (PAGE_SHIFT - 10))

/* Licencia, Descripción y Autor*/
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("This module shows information about RAM memory.");
MODULE_AUTHOR("grupo30");
 
static int meminfo_proc_show (struct seq_file *file, void *v){
    /* Se crea el struct que almacena los datos requeridos */
    struct sysinfo inf; 
    unsigned long total_memory,mem_available,mem_consumed,percent_used;

    si_meminfo(&inf);

    mem_available = si_mem_available();

    total_memory = K(inf.totalram);
    mem_available = K(si_mem_available());
    mem_consumed = total_memory-mem_available;
    percent_used = mem_consumed*100 / total_memory;

    seq_printf(file,"{\n");
    seq_printf(file,
            "   \"total_mem\": %8lu,\n"
            "   \"memory_consumed\": %8lu,\n"
            "   \"percent_use\": %8lu\n"
            ,
            total_memory,
            mem_consumed,
            percent_used
        );
    seq_printf(file,"}\n");
    return 0;
}

/* Cuando se abra el archivo se ejecuta la función meminfo_proc_show */
static int when_opening(struct inode *inode, struct file *file){
    return single_open(file,meminfo_proc_show,NULL);
}

/* Contiene las operaciones definidas para el archivo */
static struct file_operations operations = {
    .open = when_opening,
    .read = seq_read
};

/* Función que se ejecuta al momento de crear el módulo */
static int proc_meminfo_init(void){
	proc_create("mem_grupo30", 0, NULL, &operations);
	printk(KERN_INFO "%s","Hola mundo, somos el grupo 30 y este es el monitor de memoria\n");
	return 0;
}

/* Función que se ejecuta al momento de eliminar el modulo */
static void proc_meminfo_exit(void){ //al desinstalar el modulo se ejecuta
	remove_proc_entry("mem_grupo30", NULL); //remueve el archivo en proc 
	printk(KERN_INFO "Sayonara mundo, somos el grupo 30 y este fue el monitor de memoria\n");
}

module_init(proc_meminfo_init);
module_exit(proc_meminfo_exit);
