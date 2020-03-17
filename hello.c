#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/net.h>
#include <linux/inet.h>
#include <net/sock.h>

#define USE_IMMEDIATE
MODULE_LICENSE("GPL");

int hello_send(void) {
    struct socket* sock;
    struct sockaddr_in s_addr;
    unsigned short port = 8888;
    int ret = 0;
    char sendbuf[1024] = "Hello world\n";
    struct kvec vec;
    struct msghdr msg;

    /* init sock */
    memset(&s_addr, 0, sizeof(s_addr));
    s_addr.sin_family = AF_INET;
    s_addr.sin_port = htons(port);

    s_addr.sin_addr.s_addr = in_aton("127.0.0.1");
    sock = (struct socket*)kmalloc(sizeof(struct socket), GFP_KERNEL);

    /* create a socket */
    ret = sock_create_kern(&init_net, AF_INET, SOCK_STREAM, 0, &sock);
    if (ret < 0) {
        printk(KERN_ERR "socket create error!\n");
        goto CLEANUP;
    }
    printk(KERN_INFO "socket create ok!\n");

    /* connect server */
    ret =
        sock->ops->connect(sock, (struct sockaddr*)&s_addr, sizeof(s_addr), 0);
    if (ret != 0) {
        printk(KERN_ERR "connect error!\n");
        goto CLEANUP;
    }
    printk(KERN_INFO "connect ok!\n");

    /* send */
    vec.iov_base = sendbuf;
    vec.iov_len = 1024;
    memset(&msg, 0, sizeof(msg));

    ret = kernel_sendmsg(sock, &msg, &vec, 1, 1024);
    if (ret < 0) {
        printk(KERN_ERR "kernel_sendmsg error!\n");
        goto CLEANUP;
    } else if (ret != 1024) {
        printk(KERN_ERR "kernel_sendmsg ret!=1024\n");
        goto CLEANUP;
    }

    printk(KERN_INFO "send ok!\n");

CLEANUP:
    kfree(sock);
    return ret;
}

static int hello_init(void) {
    printk(KERN_INFO "Hello mod init\n");
    return (hello_send() != 1024);
}
static void hello_exit(void) { printk(KERN_INFO "Hello mod exit\n"); }

module_init(hello_init);
module_exit(hello_exit);