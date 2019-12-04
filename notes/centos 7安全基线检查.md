高确保root是唯一的UID为0的帐户 | 身份鉴别
描述

除root以外其他UID为0的用户都应该删除，或者为其分配新的UID

检查提示

--

加固建议

除root以外其他UID为0的用户(查看命令cat /etc/passwd | awk -F: '($3 == 0) { print $1 }'|grep -v '^root$')都应该删除，或者为其分配新的UID

操作时建议做好记录或备份

高开启地址空间布局随机化 | 入侵防范
描述

它将进程的内存空间地址随机化来增大入侵者预测目的地址难度，从而降低进程被成功入侵的风险

检查提示

--

加固建议

在/etc/sysctl.conf或/etc/sysctl.d/*文件中设置以下参数： kernel.randomize_va_space = 2 执行命令： sysctl -w kernel.randomize_va_space=2

操作时建议做好记录或备份

高设置用户权限配置文件的权限 | 文件权限
描述

设置用户权限配置文件的权限

检查提示

--

加固建议

执行以下5条命令

chown root:root /etc/passwd /etc/shadow /etc/group /etc/gshadow
chmod 0644 /etc/group  
chmod 0644 /etc/passwd  
chmod 0400 /etc/shadow  
chmod 0400 /etc/gshadow  
操作时建议做好记录或备份

高访问控制配置文件的权限设置 | 文件权限
描述

访问控制配置文件的权限设置

检查提示

--

加固建议

运行以下4条命令：

chown root:root /etc/hosts.allow 
chown root:root /etc/hosts.deny 
chmod 644 /etc/hosts.deny
chmod 644 /etc/hosts.allow


高确保SSH LogLevel设置为INFO | 服务配置
描述

确保SSH LogLevel设置为INFO,记录登录和注销活动

检查提示

--

加固建议

编辑 /etc/ssh/sshd_config 文件以按如下方式设置参数(取消注释):

LogLevel INFO

高确保rsyslog服务已启用 | 安全审计
描述

确保rsyslog服务已启用，记录日志用于审计

检查提示

--

加固建议

运行以下命令启用rsyslog服务：

systemctl enable rsyslog
systemctl start rsyslog


高确保SSH MaxAuthTries设置为3到6之间 | SSH服务配置
描述

设置较低的Max AuthTrimes参数将降低SSH服务器被暴力攻击成功的风险。

检查提示

--

加固建议

在/etc/ssh/sshd_config中取消MaxAuthTries注释符号#，设置最大密码尝试失败次数3-6，建议为4：

MaxAuthTries 4

高确保密码到期警告天数为7或更多 | 身份鉴别
描述

确保密码到期警告天数为7或更多

检查提示

--

加固建议

在 /etc/login.defs 中将 PASS_WARN_AGE 参数设置为7-14之间，建议为7：

PASS_WARN_AGE 7
同时执行命令使root用户设置生效：

chage --warndays 7 root


高禁止SSH空密码用户登录 | SSH服务配置
描述

 禁止SSH空密码用户登录 

检查提示

--

加固建议

编辑文件/etc/ssh/sshd_config，将PermitEmptyPasswords配置为no:

PermitEmptyPasswords no


高检查系统空密码账户 | 身份鉴别
描述

检查系统空密码账户



检查提示

--

加固建议

为用户设置一个非空密码，或者执行passwd -l <username>锁定用户


高设置SSH空闲超时退出时间 | 服务配置
描述

设置SSH空闲超时退出时间,可降低未授权用户访问其他用户ssh会话的风险

检查提示

--

加固建议

编辑/etc/ssh/sshd_config，将ClientAliveInterval 设置为300到900，即5-15分钟，将ClientAliveCountMax设置为0-3之间。

ClientAliveInterval 600
ClientAliveCountMax 2


高检查密码重用是否受限制 | 身份鉴别
描述

强制用户不重用最近使用的密码，降低密码猜测攻击风险

检查提示

--

加固建议

在/etc/pam.d/password-auth和/etc/pam.d/system-auth中password sufficient pam_unix.so 
这行的末尾配置remember参数为5-24之间，原来的内容不用更改，只在末尾加了remember=5。

高密码复杂度检查 | 身份鉴别
描述

检查密码长度和密码是否使用多种字符类型

检查提示

--

加固建议

编辑/etc/security/pwquality.conf，把minlen（密码最小长度）设置为9-32位，把minclass（至少包含小写字母、大写字母、数字、特殊字符等4类字符中等3类或4类）设置为3或4。如：

minlen=10
minclass=3


高设置密码修改最小间隔时间 | 身份鉴别
描述

设置密码修改最小间隔时间，限制密码更改过于频繁

检查提示

--

加固建议

在 /etc/login.defs 中将 PASS_MIN_DAYS 参数设置为7-14之间,建议为7：

PASS_MIN_DAYS 7
需同时执行命令为root用户设置：

chage --mindays 7 root

高设置密码失效时间 | 身份鉴别
描述

设置密码失效时间，强制定期修改密码，减少密码被泄漏和猜测风险，使用非密码登陆方式(如密钥对)请忽略此项。

检查提示

--

加固建议

使用非密码登陆方式如密钥对，请忽略此项。在 /etc/login.defs 中将 PASS_MAX_DAYS 参数设置为 60-180之间，如:

PASS_MAX_DAYS 90
需同时执行命令设置root密码失效时间：

chage --maxdays 90 root




