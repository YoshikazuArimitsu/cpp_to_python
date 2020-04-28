def dump_data(data):
    print(f'stringValue = {data.stringValue}')
    print(f'intValue = {data.intValue}')
    print(f'floatValue = {data.floatValue}')

def dump_X(x):
    print(x.value())

def dump_mv(buffer):
    print(buffer)
    mv = buffer.memoryview()
    print(type(mv))
    print(f'length = {len(mv)}')
    print(f'tobytes = {mv.tobytes()}')
