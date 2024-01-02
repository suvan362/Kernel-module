#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/init_task.h>

void dfs(struct task_struct *task, int depth) {

    struct task_struct *child_task;
    
    // Print the task name, state, and process ID
    printk(KERN_INFO "%*s %s [%d] State:%ld\n", depth*2 ,"", task->comm, task->pid,task->state);
    
    list_for_each_entry(child_task,&task->children,sibling)
    {
	dfs(child_task,depth+1);
    }
    
}

static int __init task_list_init(void) {
    printk(KERN_INFO "Task list module started\n");

    // Traverse the task list starting from the init task
    dfs(&init_task, 0);

    return 0;
}

static void __exit task_list_exit(void) {
    printk(KERN_INFO "Task list module stopped\n");
}

module_init(task_list_init);
module_exit(task_list_exit);
MODULE_LICENSE("GPL");
