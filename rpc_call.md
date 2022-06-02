# rpc_call and use

## master

### test
param:
    no param
return:
    string: "test success"

### get
param:
    file_path:string: the path of the file
return:
    vector<chunk_meta>: the chunk_node contains the file chunks, in order
    
### put
param:
    path:string: path to put the file
    name:string: file name
    size:int(?): file size
return:
    vector<address>: the address of chunk_nodes that file should sent to

### getInfo
param:
    file_path:string: the path of the file
return:
    string: some basic info of the file

### updateState
param:
    state:chunk_node_state: state of the chunk call this function
return:
    no return

### heartBeat
param:
    no param
return:
    no return


## chunk_node

### get
param:
    hash:string: the hash of the getting file
return:
    string: the file

### put
param:
    content:string: the file
    hash:string: the hash of the file
return:
    no return
