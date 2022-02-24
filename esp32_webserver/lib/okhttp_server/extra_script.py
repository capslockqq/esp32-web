Import('env')

from SCons.Script import *
cvars = env.Dictionary()
print(cvars['PIOPLATFORM'])
if "native" == cvars['PIOPLATFORM']:
    env.Replace(SRC_FILTER=["+<*.cpp>", '+<*.c>' "+<native/*.cpp>"])

elif "espressif32" == cvars['PIOPLATFORM']:
    env.Replace(SRC_FILTER=["+<*.cpp>", '+<*.c>' "+<esp32/*.cpp>"])