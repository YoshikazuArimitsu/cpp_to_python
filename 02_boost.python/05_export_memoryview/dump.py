def dump_mv(buffer):
    # Buffer から memoryview で C++ のメモリ空間を参照する
    mv = buffer.memoryview()
    print(type(mv))

    print(f'length = {len(mv)}')
    print(f'tobytes = {type(mv.tobytes())}')
    print(f'mv[:32] = {mv.tobytes()[:32]}')
