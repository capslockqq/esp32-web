Import('env')

from SCons.Script import *
cvars = env.Dictionary()
if "native" == cvars['PIOPLATFORM']:
    env.Replace(SRC_FILTER=["+<*>"])

elif "espressif32" == cvars['PIOPLATFORM']:
    env.Replace(SRC_FILTER=["-<*>"])