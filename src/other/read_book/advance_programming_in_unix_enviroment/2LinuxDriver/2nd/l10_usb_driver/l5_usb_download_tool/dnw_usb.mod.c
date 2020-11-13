#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

__visible struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0xbff2abe1, __VMLINUX_SYMBOL_STR(module_layout) },
	{ 0x97add864, __VMLINUX_SYMBOL_STR(usb_deregister) },
	{ 0xabedead0, __VMLINUX_SYMBOL_STR(usb_register_driver) },
	{ 0x2b148d37, __VMLINUX_SYMBOL_STR(usb_get_dev) },
	{ 0xd9516926, __VMLINUX_SYMBOL_STR(usb_register_dev) },
	{ 0x16f54a66, __VMLINUX_SYMBOL_STR(usb_bulk_msg) },
	{ 0x4f6b400b, __VMLINUX_SYMBOL_STR(_copy_from_user) },
	{ 0xdf3deb56, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x74cf6b1f, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x4d33b4de, __VMLINUX_SYMBOL_STR(usb_deregister_dev) },
	{ 0xbdfb6dbb, __VMLINUX_SYMBOL_STR(__fentry__) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "9829F60439AF50AB4FBC6B4");
