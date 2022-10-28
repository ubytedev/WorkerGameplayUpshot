<img src="Resources/Icon128.png" align="right" width="128px">

# WorkerGameplayUpshot
Introduces a blueprint-exposed type of Upstream Notification called Gameplay Upshot, which encapsulates the final notice about a gameplay occurrence, after privately evaluating its consequences first.

## Dependencies
- [Generic Activity Framework](https://ubyte.dev/plugins/generic-activity-framework)
- [Worker Upstream Notify](https://github.com/ubytedev/WorkerUpstreamNotify)
- [TypedTagStaticImpl](https://github.com/ubytedev/TypedTagStaticImpl)

## Example
```cpp
USTRUCT()
struct FTestAgentGameplayUpshotSet /*final*/ : public FAgentGameplayUpshotFieldSetBase
{
    GENERATED_BODY()

    // This constructor attempts to fill all soft tag body properties with its corresponding tag value.
    FTestAgentGameplayUpshotSet() { TSoftTagBodyStatics<TRemovePointer<decltype(this)>::Type>::InitFields<FAgentGameplayUpshotTag>(this); }

    UPROPERTY(VisibleAnywhere, Meta = (SoftTagBody = true))
    FAgentGameplayUpshotTag Damaged;

    UPROPERTY(VisibleAnywhere, Meta = (SoftTagBody = true))
    FAgentGameplayUpshotTag AgentDetected;
};
```
