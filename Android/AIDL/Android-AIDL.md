# AIDL

## 目的
了解AIDL的使用方式，从而总结AIDL通信方式的优势和缺点




## 实现通信实例
实现服务端APP计算客户端APP传送的数据。
### AIDL接口
```
// IAIDLInterface.aidl
package com.wes.myaidltest;

// Declare any non-default types here with import statements

interface IAIDLInterface {
    int getSum(int a, int b);

    String getName();
}
```

### 服务端
- 实现在服务段实现AIDL接口
```

public class AIDLInterfaceServer extends Service {
    public AIDLInterfaceServer() {
    }

    public void onCreate(){
        Log.i("remote Server intface", "onCreate");
    }

    @Override
    public IBinder onBind(Intent intent) {
        Log.i("remote Server intface", "onBind");
        // TODO: Return the communication channel to the service.
        //throw new UnsupportedOperationException("Not yet implemented");
        return binder;
    }

    private final IAIDLInterface.Stub binder = new IAIDLInterface.Stub() {
        public int getSum(int a, int b)
        {
            return a+b;
        }

        public String getName()
        {
            return "test name";
        }

    };

}
```

- AndroidManifext.xml配置, 注意intent-filter需要写明是AIDL接口的名称
```
<service
    android:name=".AIDLInterfaceServer"
    android:exported="true" >
    <intent-filter>
        <action android:name="com.wes.myaidltest.IAIDLInterface"></action>
    </intent-filter>
</service>
```

### 客户端
- 绑定接口服务
```
private void initService()
{
    Intent intent = new Intent();
    intent.setAction(IAIDLInterface.class.getName());
    intent.setPackage("com.wes.myaidltest");
    boolean ret = bindService(intent, serviceConnection, BIND_AUTO_CREATE);
    Log.i("clientAIDL", "bindService:" + ret);
}
```
- 获取AIDL接口连接
```
private IAIDLInterface mAIDLInterface;

private ServiceConnection serviceConnection = new ServiceConnection() {
    @Override
    public void onServiceConnected(ComponentName componentName, IBinder iBinder) {
        mAIDLInterface = IAIDLInterface.Stub.asInterface(iBinder);
        Log.i("clientAIDL", "onServiceConnected");
        try {
            if(mAIDLInterface != null)
                Log.i("clientAIDL", "bindService:" + mAIDLInterface.getSum(3, 4));
        } catch (RemoteException e) {
            e.printStackTrace();
        }
    }

    @Override
    public void onServiceDisconnected(ComponentName componentName) {
        Log.i("clientAIDL", "onServiceDisconnected");
        mAIDLInterface = null;

    }
};
```