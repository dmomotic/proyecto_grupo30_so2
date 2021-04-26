
#include <linux/proc_fs.h>
#include <linux/hugetlb.h>
#include <linux/module.h> 
#include <linux/sched/signal.h>

/* Obtiene el dato en kilobytes */
#define K(x) ((x) << (PAGE_SHIFT - 10))

  /*PROCESOS*/

    unsigned int total = 0;
    unsigned int ejecucion = 0;
    unsigned int suspendidos = 0;
    unsigned int detenidos = 0;
    unsigned int zombies = 0;
    unsigned int otros = 0;


/* Licencia, Descripción y Autor*/
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("This module shows information about CPU.");
MODULE_AUTHOR("Grupo 30");

char * get_task_state (long state){

    total++;
    switch (state)
    {
        case TASK_RUNNING: ejecucion++; return "Running";
        case TASK_INTERRUPTIBLE: suspendidos++; return "Sleeping";
        case TASK_UNINTERRUPTIBLE: suspendidos++; return "Sleeping";
        case __TASK_STOPPED:  detenidos++; return "Stopped";
        case __TASK_TRACED:  detenidos++; return "Stopped";
        case TASK_STOPPED:  detenidos++; return "Stopped";
        case EXIT_ZOMBIE: zombies++; return "Zombie";
        default: otros++; return "Unknown";
    }

}

static int cpuinfo_proc_show (struct seq_file *file, void *v){ 

    total = 0;
    ejecucion = 0;
    suspendidos = 0;
    detenidos = 0;
    zombies = 0;
    otros = 0;



    /* Contiene el proceso */
    struct task_struct *task;
    /* Contiene el hijo de un proceso */
    struct task_struct *task_child;
    /* Contiene una lista con los  procesos */
    struct list_head *list;

    unsigned long memory;
    int cantp=0,cantp1=0,cantpch=0,cantpch1=0;

    seq_printf(file, "{\n");
    
    seq_printf(file, "\"children\":\n");
    
    seq_printf(file,"[\n");
    for_each_process( task ){cantp++;}
    for_each_process( task ){
        memory=task->mm!=NULL?get_mm_rss(task->mm):0;
        seq_printf(file,"{\n");
        seq_printf(file, 
            "   \"pid\": %5d,\n"
            "   \"user\": %5d,\n"
            "   \"state\": \"%s\",\n"
            "   \"memory\": %lu,\n"
            "   \"name\": \"%s\",\n"
            "   \"children\": ["
            ,
            task->pid,
            from_kuid(&init_user_ns, task_uid(task)),
            get_task_state(task->state),
            memory,
            task->comm
        );
        list_for_each(list, &task->children){cantpch++;}
        list_for_each(list, &task->children){
            task_child = list_entry( list, struct task_struct, sibling );
            memory=task_child->mm!=NULL?get_mm_rss(task_child->mm):0;
            seq_printf(file,"\n                 {\n");
            seq_printf(file, 
                "                     \"pid\": %5d,\n"
                "                     \"fpid\": %5d,\n"
                "                     \"user\": %5d,\n"
                "                     \"state\": \"%s\",\n"
                "                     \"memory\": %lu,\n"
                "                     \"name\": \"%s\"\n"	
                , 
                task_child->pid,
                task->pid,
                from_kuid(&init_user_ns, task_uid(task)),	
                get_task_state(task_child->state),
                memory,
                task_child->comm
            );
            cantpch1++;
            if(cantpch!=cantpch1) seq_printf(file,"\n                 },\n");
            else seq_printf(file,"\n                 }\n");
        }
        seq_printf(file,"]\n");

        cantp1++;
        if(cantp!=cantp1) seq_printf(file,"},\n");
        else seq_printf(file,"}\n");
  
    }
  
    seq_printf(file,"],\n");
    seq_printf(file, "\"ejecucion\":%d,\n", ejecucion);
    seq_printf(file, "\"suspendidos\":%d,\n", suspendidos);
    seq_printf(file, "\"detenidos\":%d,\n", detenidos);
    seq_printf(file, "\"zombies\":%d,\n", zombies);
    seq_printf(file, "\"otros\":%d,\n", otros);
    seq_printf(file, "\"total\":%d\n", total);
    seq_printf(file, "}\n");

   

    return 0;
}

/* Cuando se abra el archivo se ejecuta la función cpuinfo_proc_show */
static int when_opening(struct inode *inode, struct file *file){
    return single_open(file,cpuinfo_proc_show,NULL);
}

/* Contiene las operaciones definidas para el archivo */
static struct file_operations operations = {
    .open = when_opening,
    .read = seq_read
};

/* Función que se ejecuta al momento de crear el módulo */
static int proc_meminfo_init(void){
	proc_create("cpu_grupo30", 0, NULL, &operations);
	printk(KERN_INFO "%s","Hola mundo, somos el grupo 30 y este es el monitor de procesos\n");
	return 0;
}

/* Función que se ejecuta al momento de eliminar el modulo */
static void proc_meminfo_exit(void){ //al desinstalar el modulo se ejecuta
	remove_proc_entry("cpu_grupo30", NULL); //remueve el archivo en proc 
	printk(KERN_INFO "Sayonaramundo, somos el grupo 30 y este fue el monitor de procesos\n");
}

module_init(proc_meminfo_init);
module_exit(proc_meminfo_exit);
