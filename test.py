import numpy as np
import fpread

print("before:", hex(fpread._control87() & fpread._MCW_PC))
np.absolute(complex(np.inf, 0))
print("after:", hex(fpread._control87() & fpread._MCW_PC))
