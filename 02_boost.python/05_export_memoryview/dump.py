def dump_mv(buffer):
    mv = buffer.memoryview()
    print(type(mv))
    print(f'length = {len(mv)}')
    print(f'tobytes = {type(mv.tobytes())}')
