def endpoint_file():
    with open('data.bin', 'rb') as f:
        content = f.read()

def endpoint_memoryview(buffer):
    mv = buffer.memoryview()
    contents = bytes(mv)
