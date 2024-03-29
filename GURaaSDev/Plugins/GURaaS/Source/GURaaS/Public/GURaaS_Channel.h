#pragma once

#include "EVerboseLevel.h"
#include "CoreMinimal.h"

#include "GURaaS_Channel.generated.h"

USTRUCT(Blueprintable)
struct FSessionInfo
{
	GENERATED_BODY()

public:
	UPROPERTY() FString m_GameId;
	UPROPERTY() FString m_SessionId;
	UPROPERTY() FString m_PlayerId;
	UPROPERTY() FString m_Context;
	UPROPERTY() FDateTime m_SessionStart;
	UPROPERTY() FDateTime m_SessionEnd;

	FSessionInfo() :
		m_GameId(""),
		m_SessionId(""),
		m_SessionStart(FDateTime::Now()),
		m_SessionEnd(FDateTime::Now())
	{
	}

	FSessionInfo(FString GameId, FString SessionId, FString PlayerId, FString Context, FDateTime SessionStart)
		: m_GameId(GameId)
		, m_SessionId(SessionId)
		, m_PlayerId(PlayerId)
		, m_Context(Context)
		, m_SessionStart(SessionStart)
		, m_SessionEnd(SessionStart)
	{
	}

	FSessionInfo(FString GameId, FString SessionId, FString PlayerId, FString Context, FDateTime SessionStart, FDateTime SessionEnd)
		: m_GameId(GameId)
		, m_SessionId(SessionId)
		, m_PlayerId(PlayerId)
		, m_Context(Context)
		, m_SessionStart(SessionStart)
		, m_SessionEnd(SessionEnd)
	{
	}

	FSessionInfo(const FSessionInfo& Other)
		: m_GameId(Other.m_GameId)
		, m_SessionId(Other.m_SessionId)
		, m_PlayerId(Other.m_PlayerId)
		, m_Context(Other.m_Context)
		, m_SessionStart(Other.m_SessionStart)
		, m_SessionEnd(Other.m_SessionEnd)
	{
	}

};

USTRUCT(Blueprintable)
struct FGURaaSLogEntry{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly, Category = "GURaaS") FString Time;
	UPROPERTY(BlueprintReadOnly, Category = "GURaaS") FString Tag1;
	UPROPERTY(BlueprintReadOnly, Category = "GURaaS") FString Tag2;
	UPROPERTY(BlueprintReadOnly, Category = "GURaaS") FString Tag3;
	UPROPERTY(BlueprintReadOnly, Category = "GURaaS") FString Tag4;
	UPROPERTY(BlueprintReadOnly, Category = "GURaaS") FString Data;
};

UCLASS(Blueprintable)
class GURAAS_API UGLogChannel : public UObject
{
	GENERATED_BODY()
		
public:

	UFUNCTION(BlueprintCallable, Category = "GURaaS")
		virtual void Log(EGURaaSVerboseLevel VerboseLevel, const FString& Message, const FString& Tag1, const FString& Tag2, const FString& Tag3) {};

	UFUNCTION(BlueprintCallable, Category = "GURaaS")
		virtual void StartSession(FSessionInfo SessionInfo);

	UFUNCTION(BlueprintCallable, Category = "GURaaS")
		virtual void EndSession() {}

	UFUNCTION(BlueprintCallable, Category = "GURaaS")
		virtual void Flush() {}

protected:

	UPROPERTY(BlueprintReadWrite, Category = "GURaaS")
	FSessionInfo m_SessionInfo;

};

UCLASS(Blueprintable)
class GURAAS_API UGLogChannelGURaaS : public UGLogChannel
{
	GENERATED_BODY()

		UGLogChannelGURaaS();
	
public:
		virtual void Log(EGURaaSVerboseLevel VerboseLevel, const FString& Message, const FString& Tag1, const FString& Tag2, const FString& Tag3) override;
		virtual void Flush() override;

private:
	void Process();

private:
	
	//const FString m_Url = "http://127.0.0.1:9002";
	const FString m_Url = "https://grg.service.guraas.com";

	struct LogEntry
	{
		EGURaaSVerboseLevel m_VerboseLevel;
		FString m_Message;
		FString m_Tag1;
		FString m_Tag2;
		FString m_Tag3;
		FDateTime m_TimeStamp;
	};
	
	TArray<LogEntry> m_LogEntries;
};

UCLASS(Blueprintable)
class GURAAS_API UGLogChannelConsole : public UGLogChannel
{
	GENERATED_BODY()

public:
		virtual void Log(EGURaaSVerboseLevel VerboseLevel, const FString& Message, const FString& Tag1, const FString& Tag2, const FString& Tag3) override;
};


