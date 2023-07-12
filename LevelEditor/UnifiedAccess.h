#pragma once

#include <memory>
#include "Event.h"
#include <Function/Function.h>
#include <Function/FunctionTraits.h>
#include <Function/Invoke.h>
#include <wx/listbox.h>

namespace Creation
{
    /*
    template<class T>
    class UnifiedAccess
    {
    public:
        typedef T VariableT;
    private:
        union U
        {
            VariableT *var;
            std::unique_ptr<VariableT> uniPtr;
            U();
            U(VariableT *var);
            U(VariableT &&var);
            ~U();
        };

        enum class Type
        {
            VAR,
            UNI_PTR
        };
    private:
        U u;
        Type type;

        void MoveU(UnifiedAccess &&arg);
    public:
        UnifiedAccess(VariableT *var);
        UnifiedAccess(VariableT &var);
        UnifiedAccess(VariableT &&var);
        UnifiedAccess(UnifiedAccess &&arg);
        UnifiedAccess& operator=(UnifiedAccess &&arg);

        operator VariableT&();
        operator const VariableT&() const;
        VariableT* operator->();
        const VariableT* operator->() const;
        VariableT& operator*();
        const VariableT& operator*() const;
        VariableT& Get();
        const VariableT& Get() const;

        // If this is false, then the held item is not the original
        bool Original() const;
    };

    template<class T>
    UnifiedAccess<T>::U::U() : var(nullptr)
    {}

    template<class T>
    UnifiedAccess<T>::U::U(VariableT *var) : var(var)
    {}

    template<class T>
    UnifiedAccess<T>::U::U(VariableT &&var) : uniPtr(new VariableT(std::move(var)))
    {}

    template<class T>
    UnifiedAccess<T>::U::~U()
    {}

    template<class T>
    void UnifiedAccess<T>::MoveU(UnifiedAccess &&arg)
    {
        switch (type)
        {
        case Type::VAR:
            u.var = arg.u.var;
            break;
        case Type::UNI_PTR:
            u.uniPtr = std::move(arg.u.uniPtr);
            break;
        }
    }

    template<class T>
    UnifiedAccess<T>::UnifiedAccess(VariableT *var) : u(var), type(Type::VAR)
    {}

    template<class T>
    UnifiedAccess<T>::UnifiedAccess(VariableT &var) : u(&var), type(Type::VAR)
    {}

    template<class T>
    UnifiedAccess<T>::UnifiedAccess(VariableT &&var) : u(std::move(var)), type(Type::UNI_PTR)
    {}

    template<class T>
    UnifiedAccess<T>::UnifiedAccess(UnifiedAccess &&arg) : type(std::move(arg.type))
    {
        MoveU(std::move(arg));
    }

    template<class T>
    UnifiedAccess<T>& UnifiedAccess<T>::operator=(UnifiedAccess &&arg)
    {
        type = std::move(arg.type);
        MoveU(std::move(arg));
        return *this;
    }

    template<class T>
    UnifiedAccess<T>::operator VariableT&()
    {
        return Get();
    }

    template<class T>
    UnifiedAccess<T>::operator const VariableT&() const
    {
        return Get();
    }

    template<class T>
    typename UnifiedAccess<T>::VariableT* UnifiedAccess<T>::operator->()
    {
        return &Get();
    }

    template<class T>
    typename const UnifiedAccess<T>::VariableT* UnifiedAccess<T>::operator->() const
    {
        return &Get();
    }

    template<class T>
    typename UnifiedAccess<T>::VariableT& UnifiedAccess<T>::operator*()
    {
        return Get();
    }

    template<class T>
    typename const UnifiedAccess<T>::VariableT& UnifiedAccess<T>::operator*() const
    {
        return Get();
    }

    template<class T>
    typename UnifiedAccess<T>::VariableT& UnifiedAccess<T>::Get()
    {
        switch (type)
        {
        case Type::VAR:
            return *u.var;
        case Type::UNI_PTR:
            return *u.uniPtr.get();
        }

        return *u.var;
    }

    template<class T>
    typename const UnifiedAccess<T>::VariableT& UnifiedAccess<T>::Get() const
    {
        switch (type)
        {
        case Type::VAR:
            return *u.var;
        case Type::UNI_PTR:
            return *u.uniPtr.get();
        }

        return *u.var;
    }

    template<class T>
    bool UnifiedAccess<T>::Original() const
    {
        if (type == Type::UNI_PTR)
            return false;

        return true;
    }
    */

/*
    class UnifiedAccessHandlerBase;
    class UnifiedAccessEditArgs
    {
    private:
        const void *prev;
        UnifiedAccessHandlerBase *handler;
    public:
        UnifiedAccessEditArgs(const void *prev, UnifiedAccessHandlerBase *handler);
        const void* Prev() const;
        UnifiedAccessHandlerBase* Handler() const;
    };

    class UnifiedAccessHandlerBase
    {
    public:
        virtual ~UnifiedAccessHandlerBase() = 0 {}
    };

    template<class T>
    class UnifiedAccessHandler : public UnifiedAccessHandlerBase
    {
    public:
        typedef T VariableT;
        typedef UnifiedAccess<T> ReturnT;

        typedef typename std::remove_const<VariableT>::type VariableMoveT;

        typedef ::function::Function<VariableT&> GetFuncT;
    public:
        template<class Y, class Getter>
        struct IsSameChecker
        {
            static constexpr bool value = std::is_same<typename std::remove_reference<typename std::remove_const<typename ::function::FunctionTraits<Getter>::ReturnT>::type>::type, Y>::value;
        };

        template<class Y, class Getter>
        struct IsSameChecker<const Y, Getter>
        {
            static constexpr bool value = std::is_same<typename std::remove_reference<typename ::function::FunctionTraits<Getter>::ReturnT>::type, Y>::value;
        };

        class Base
        {
        public:
            virtual Base* Clone() const = 0;
            virtual ReturnT Get() = 0;
            virtual void Set(const VariableT &set) = 0;
        };

        template<class Getter, class Setter>
        class CopyDerived : public Base
        {
        private:
            static_assert(IsSameChecker<VariableT, Getter>::value, "The getter function given does not return the same type as this UnifiedAccessHandler.");
        public:
            Getter getter;
            Setter setter;
            CopyDerived(Getter &&getter, Setter &&setter);
            CopyDerived(const CopyDerived &arg) = default;
            CopyDerived& operator=(const CopyDerived &arg) = default;
            CopyDerived* Clone() const override final;
            ReturnT Get() override final;
            void Set(const VariableT &set) override final;
        };

        template<class Getter, class Setter>
        class MoveDerived : public Base
        {
        private:
            static_assert(IsSameChecker<VariableT, Getter>::value, "The getter function given does not return the same type as this UnifiedAccessHandler.");
        public:
            Getter getter;
            Setter setter;
            MoveDerived(Getter &&getter, Setter &&setter);
            MoveDerived(const MoveDerived &arg);
            MoveDerived& operator=(const MoveDerived &arg) = default;
            MoveDerived* Clone() const override final;
            ReturnT Get() override final;
            void Set(const VariableT &set) override final;
        };

        union U
        {
            VariableT *ptr;
            GetFuncT getRef;
            std::unique_ptr<Base> base;
            U();
            ~U();
            void Set(VariableT *ptr);
            void Set(GetFuncT &&getRef);
            void Set(Base *base);
        };

        enum class Type : unsigned char
        {
            NONE,

            PTR,
            GET_REF,
            BASE
        };
    private:
        bool valid;
        bool editable;

        U u;
        Type type;

        void CopyU(const UnifiedAccessHandler &arg);
        void MoveU(UnifiedAccessHandler &&arg);

        void SetupCommon(VariableT *ptr);
        void SetupCommon(GetFuncT &&getRef);
        template<class Getter>
        void SetupCommon(Getter &&getter, ::function::Function<void, VariableT> &&setter);
        template<class Getter>
        void SetupCommon(Getter &&getter, ::function::Function<void, const VariableT&> &&setter);
        template<class Getter>
        void SetupCommon(Getter &&getter, ::function::Function<void, VariableMoveT&&> &&setter);

        virtual void OnEdited() {}
        virtual void SetupInner() {}
        virtual void OnSetEditable(bool set) {}
    public:
        Event<const UnifiedAccessEditArgs&> edited;

        UnifiedAccessHandler();
        UnifiedAccessHandler(const UnifiedAccessHandler &arg);
        UnifiedAccessHandler(UnifiedAccessHandler &&arg);
        UnifiedAccessHandler& operator=(const UnifiedAccessHandler &arg);
        UnifiedAccessHandler& operator=(UnifiedAccessHandler &&arg);
        virtual ~UnifiedAccessHandler() = 0 {}

        void Setup(VariableT *ptr, bool valid = true);
        template<class Getter, class ObjT>
        void Setup(Getter getter, ObjT *obj, bool valid = true);
        template<class Getter, class ObjT>
        void Setup(Getter getter, UnifiedAccess<ObjT> *obj, bool valid = true);
        template<class Getter, class Setter, class ObjT>
        void Setup(Getter getter, Setter setter, ObjT *obj, bool valid = true);
        template<class Getter, class Setter, class ObjT>
        void Setup(Getter getter, Setter setter, UnifiedAccess<ObjT> *obj, bool valid = true);
        template<class GetterRet>
        void Setup(::function::Function<GetterRet> &&getter, bool valid = true);
        template<class GetterRet, class... SetterArgs>
        void Setup(::function::Function<GetterRet> &&getter, ::function::Function<void, SetterArgs...> &&setter, bool valid = true);

        void Edit(const VariableT &arg);
        void Edit(VariableMoveT &&arg);
        ReturnT Get() const;

        void SetValid(bool set);
        bool IsValid() const;
        void SetEditable(bool set);
        bool IsEditable() const;
    };

    template<class T>
    template<class Getter, class Setter>
    UnifiedAccessHandler<T>::CopyDerived<Getter, Setter>::CopyDerived(Getter &&getter, Setter &&setter) : getter(std::move(getter)), setter(std::move(setter))
    {}

    template<class T>
    template<class Getter, class Setter>
    UnifiedAccessHandler<T>::CopyDerived<Getter, Setter>* UnifiedAccessHandler<T>::CopyDerived<Getter, Setter>::Clone() const
    {
        return new CopyDerived(*this);
    }

    template<class T>
    template<class Getter, class Setter>
    typename UnifiedAccessHandler<T>::ReturnT UnifiedAccessHandler<T>::CopyDerived<Getter, Setter>::Get()
    {
        return ReturnT(getter());
    }

    template<class T>
    template<class Getter, class Setter>
    void UnifiedAccessHandler<T>::CopyDerived<Getter, Setter>::Set(const VariableT &set)
    {
        setter(set);
    }

    template<class T>
    template<class Getter, class Setter>
    UnifiedAccessHandler<T>::MoveDerived<Getter, Setter>::MoveDerived(Getter &&getter, Setter &&setter) : getter(std::move(getter)), setter(std::move(setter))
    {}

    template<class T>
    template<class Getter, class Setter>
    UnifiedAccessHandler<T>::MoveDerived<Getter, Setter>::MoveDerived(const MoveDerived &arg) : getter(arg.getter), setter(arg.setter)
    {}

    template<class T>
    template<class Getter, class Setter>
    UnifiedAccessHandler<T>::MoveDerived<Getter, Setter>* UnifiedAccessHandler<T>::MoveDerived<Getter, Setter>::Clone() const
    {
        return new MoveDerived(*this);
    }

    template<class T>
    template<class Getter, class Setter>
    typename UnifiedAccessHandler<T>::ReturnT UnifiedAccessHandler<T>::MoveDerived<Getter, Setter>::Get()
    {
        return getter();
    }

    template<class T>
    template<class Getter, class Setter>
    void UnifiedAccessHandler<T>::MoveDerived<Getter, Setter>::Set(const VariableT &set)
    {
        setter(std::move(VariableT(set)));
    }

    template<class T>
    UnifiedAccessHandler<T>::U::U() : ptr(nullptr)
    {}

    template<class T>
    UnifiedAccessHandler<T>::U::~U()
    {}

    template<class T>
    void UnifiedAccessHandler<T>::U::Set(VariableT *ptr)
    {
        this->ptr = ptr;
    }

    template<class T>
    void UnifiedAccessHandler<T>::U::Set(GetFuncT &&getRef)
    {
        this->getRef = std::move(getRef);
    }

    template<class T>
    void UnifiedAccessHandler<T>::U::Set(Base *base)
    {
        this->base.reset(base);
    }

    template<class T>
    void UnifiedAccessHandler<T>::CopyU(const UnifiedAccessHandler &arg)
    {
        switch (type)
        {
        case Type::PTR:
            u.ptr = arg.u.ptr;
            break;
        case Type::GET_REF:
            u.getRef = arg.u.getRef;
            break;
        case Type::BASE:
            u.base = arg.u.base;
            break;
        }
    }

    template<class T>
    void UnifiedAccessHandler<T>::MoveU(UnifiedAccessHandler &&arg)
    {
        switch (type)
        {
        case Type::PTR:
            u.ptr = std::move(arg.u.ptr);
            break;
        case Type::GET_REF:
            u.getRef = std::move(arg.u.getRef);
            break;
        case Type::BASE:
            u.base = std::move(arg.u.base);
            break;
        }
    }

    template<class T>
    void UnifiedAccessHandler<T>::SetupCommon(VariableT *ptr)
    {
        if (!IsValid())
        {
            type = Type::NONE;
            return;
        }

        u.Set(ptr);
        type = Type::PTR;
    }

    template<class T>
    void UnifiedAccessHandler<T>::SetupCommon(GetFuncT &&getRef)
    {
        if (!IsValid())
        {
            type = Type::NONE;
            return;
        }

        u.Set(std::move(getRef));
        type = Type::GET_REF;
    }

    template<class T>
    template<class Getter>
    void UnifiedAccessHandler<T>::SetupCommon(Getter &&getter, ::function::Function<void, VariableT> &&setter)
    {
        if (!IsValid())
        {
            type = Type::NONE;
            return;
        }

        u.Set(new MoveDerived<Getter, ::function::Function<void, VariableT>>(std::move(getter), std::move(setter)));
        type = Type::BASE;
    }

    template<class T>
    template<class Getter>
    void UnifiedAccessHandler<T>::SetupCommon(Getter &&getter, ::function::Function<void, const VariableT&> &&setter)
    {
        if (!IsValid())
        {
            type = Type::NONE;
            return;
        }

        u.Set(new CopyDerived<Getter, ::function::Function<void, const VariableT&>>(std::move(getter), std::move(setter)));
        type = Type::BASE;
    }

    template<class T>
    template<class Getter>
    void UnifiedAccessHandler<T>::SetupCommon(Getter &&getter, ::function::Function<void, VariableMoveT&&> &&setter)
    {
        if (!IsValid())
        {
            type = Type::NONE;
            return;
        }

        u.Set(new MoveDerived<Getter, ::function::Function<void, VariableMoveT&&>>(std::move(getter), std::move(setter)));
        type = Type::BASE;
    }

    template<class T>
    UnifiedAccessHandler<T>::UnifiedAccessHandler() : valid(false), editable(true), type(Type::NONE)
    {}

    template<class T>
    UnifiedAccessHandler<T>::UnifiedAccessHandler(const UnifiedAccessHandler &arg) : valid(arg.valid), editable(arg.editable), type(arg.type), edited(arg.edited)
    {
        CopyU(arg);
    }

    template<class T>
    UnifiedAccessHandler<T>::UnifiedAccessHandler(UnifiedAccessHandler &&arg) : valid(std::move(arg.valid)), editable(std::move(arg.editable)), type(std::move(arg.type)), edited(std::move(arg.edited))
    {
        MoveU(std::move(arg));
    }

    template<class T>
    UnifiedAccessHandler<T>& UnifiedAccessHandler<T>::operator=(const UnifiedAccessHandler &arg)
    {
        valid = arg.valid;
        editable = arg.editable;
        type = arg.type;
        CopyU(arg);
        return *this;
    }

    template<class T>
    UnifiedAccessHandler<T>& UnifiedAccessHandler<T>::operator=(UnifiedAccessHandler &&arg)
    {
        valid = std::move(arg.valid);
        editable = std::move(arg.editable);
        type = std::move(arg.type);
        MoveU(std::move(arg));
        return *this;
    }

    template<class T>
    void UnifiedAccessHandler<T>::Setup(VariableT *ptr, bool valid)
    {
        static_assert(!std::is_const<VariableT>::value, "You cannot give a UnifiedAccessHandler a const variable unless you give it a setter.");

        SetValid(valid && ptr);
        SetupCommon(ptr);
        SetupInner();
    }

    template<class T>
    template<class Getter, class ObjT>
    void UnifiedAccessHandler<T>::Setup(Getter getter, ObjT *obj, bool valid)
    {
        static_assert(!std::is_const<VariableT>::value, "You cannot give a UnifiedAccessHandler a const variable unless you give it a setter.");

        SetValid(valid);
        SetupCommon(::function::CreateFunction(getter, obj));
        SetupInner();
    }

    template<class T>
    template<class Getter, class ObjT>
    void UnifiedAccessHandler<T>::Setup(Getter getter, UnifiedAccess<ObjT> *obj, bool valid)
    {
        Setup(getter, &*obj, valid);
    }

    template<class T>
    template<class Getter, class Setter, class ObjT>
    void UnifiedAccessHandler<T>::Setup(Getter getter, Setter setter, ObjT *obj, bool valid)
    {
        SetValid(valid);
        SetupCommon(::function::CreateFunction(getter, obj), ::function::CreateFunction(setter, obj));
        SetupInner();
    }

    template<class T>
    template<class Getter, class Setter, class ObjT>
    void UnifiedAccessHandler<T>::Setup(Getter getter, Setter setter, UnifiedAccess<ObjT> *obj, bool valid)
    {
        Setup(getter, setter, &**obj, valid);
    }

    template<class T>
    template<class GetterRet>
    void UnifiedAccessHandler<T>::Setup(::function::Function<GetterRet> &&getter, bool valid)
    {
        static_assert(!std::is_const<VariableT>::value, "You cannot give a UnifiedAccessHandler a const variable unless you give it a setter.");

        SetValid(valid);
        SetupCommon(std::move(getter));
        SetupInner();
    }

    template<class T>
    template<class GetterRet, class... SetterArgs>
    void UnifiedAccessHandler<T>::Setup(::function::Function<GetterRet> &&getter, ::function::Function<void, SetterArgs...> &&setter, bool valid)
    {
        SetValid(valid);
        SetupCommon(std::move(getter), std::move(setter));
        SetupInner();
    }

    template<class T>
    void UnifiedAccessHandler<T>::Edit(const VariableT &arg)
    {
        if (!IsEditable())
            return;

        auto test = *Get();
        void *prev = &test;
        UnifiedAccessEditArgs args(prev, this);
        switch (type)
        {
        case Type::PTR:
            const_cast<VariableMoveT&>(*u.ptr) = arg;
            OnEdited();
            edited(args);
            break;
        case Type::GET_REF:
            const_cast<VariableMoveT&>(u.getRef()) = arg;
            OnEdited();
            edited(args);
            break;
        case Type::BASE:
            u.base->Set(arg);
            OnEdited();
            edited(args);
            break;
        }
    }

    template<class T>
    void UnifiedAccessHandler<T>::Edit(VariableMoveT &&arg)
    {
        if (!IsEditable())
            return;

        auto test = *Get();
        void *prev = &test;
        UnifiedAccessEditArgs args(prev, this);
        switch (type)
        {
        case Type::PTR:
            const_cast<VariableMoveT&>(*u.ptr) = std::move(arg);
            OnEdited();
            edited(args);
            break;
        case Type::GET_REF:
            const_cast<VariableMoveT&>(u.getRef()) = std::move(arg);
            OnEdited();
            edited(args);
            break;
        case Type::BASE:
            u.base->Set(std::move(arg));
            OnEdited();
            edited(args);
            break;
        }
    }

    template<class T>
    typename UnifiedAccessHandler<T>::ReturnT UnifiedAccessHandler<T>::Get() const
    {
        switch (type)
        {
        case Type::PTR:
            return ReturnT(u.ptr);
        case Type::GET_REF:
            return ReturnT(u.getRef());
        case Type::BASE:
            return ReturnT(u.base->Get());
        }

        return ReturnT(nullptr);
    }

    template<class T>
    void UnifiedAccessHandler<T>::SetValid(bool set)
    {
        valid = set;
    }

    template<class T>
    bool UnifiedAccessHandler<T>::IsValid() const
    {
        return valid;
    }

    template<class T>
    void UnifiedAccessHandler<T>::SetEditable(bool set)
    {
        if (editable == set)
            return;

        editable = set;
        OnSetEditable(editable);
    }

    template<class T>
    bool UnifiedAccessHandler<T>::IsEditable() const
    {
        return editable;
    }

    template<class T, class Object, class FindReturn, class IDPass, class IDFuncPass, class AddArgsPack = ::function::VariadicTemplate<>, class... CreateArgs>
    class UnifiedAccessHandlerList : public UnifiedAccessHandlerBase
    {
    public:
        typedef T VariableT;
        typedef Object ObjectT;
        typedef FindReturn FindReturnT;
        typedef IDPass ID;
        typedef IDFuncPass FuncID;

        typedef typename VariableT::const_iterator const_iterator;

        typedef typename AddArgsPack::TupleT AddArgsTupleT;
    private:
        // Remover of const and references
        template<class T>
        struct CreateArgsTransformer
        {
            typedef typename std::remove_const<typename std::remove_reference<T>::type>::type Type;
        };
    public:
        // Tuple of all of the create args minus references and const
        typedef typename ::function::VariadicTemplate<CreateArgs...>::template Transform<CreateArgsTransformer>::Type::TupleT CreateArgsTupleT;

        typedef ::function::Function<VariableT&> GetFuncT;
        typedef ::function::Function<ID, CreateArgs...> CreateFuncT;
        typedef ::function::Function<FindReturnT, IDFuncPass> FindFuncT;
        typedef ::function::Function<void, IDFuncPass> DeleteFuncT;
    private:
        enum class Type
        {
            NONE,
            VAR,
            FUNC
        };

        union U
        {
            VariableT *var;
            GetFuncT getFunc;
            U();
            ~U();
        };
    private:
        bool valid;
        bool editable;

        Type type;
        U u;

        CreateFuncT createFunc;
        FindFuncT findFunc;
        DeleteFuncT removeFunc;

        void CopyU(const UnifiedAccessHandlerList &arg);
        void MoveU(UnifiedAccessHandlerList &&arg);

        void SetupCommonVariable(VariableT *var, CreateFuncT &&createFunc, FindFuncT &&findFunc, DeleteFuncT &&removeFunc);
        void SetupCommonFunction(GetFuncT &&getFunc, CreateFuncT &&createFunc, FindFuncT &&findFunc, DeleteFuncT &&removeFunc);
        
        virtual void OnEdited() {}
        virtual void SetupInner() {}
        virtual bool CanAdd(const AddArgsTupleT &add, const CreateArgsTupleT &create) { return true; }
        virtual void OnAdd(const AddArgsTupleT &add, const CreateArgsTupleT &create, ID &ret) {}
        virtual void PreRemove(FuncID id) {}
        virtual void OnRemove(FuncID id) {}
        virtual void OnSetEditable(bool set) {}

        virtual FindReturnT GetInvalidObjectReturnImpl() const = 0;
        virtual ID GetInvalidIDReturnImpl() const = 0;
        virtual ObjectT& ExtractObjectImpl(FindReturnT findReturn) = 0;
    protected:
        FindReturnT GetInvalidObjectReturn() const;
        ID GetInvalidIDReturn() const;
    public:
        Event<UnifiedAccessHandlerBase*, FuncID> added;
        Event<UnifiedAccessHandlerBase*, FuncID> removed;
        Event<UnifiedAccessHandlerBase*> edited;

        UnifiedAccessHandlerList();
        UnifiedAccessHandlerList(const UnifiedAccessHandlerList &arg);
        UnifiedAccessHandlerList(UnifiedAccessHandlerList &&arg);
        UnifiedAccessHandlerList& operator=(const UnifiedAccessHandlerList &arg);
        UnifiedAccessHandlerList& operator=(UnifiedAccessHandlerList &&arg);
        virtual ~UnifiedAccessHandlerList() = 0 {}

        template<class Creator, class Finder, class Deleter, class ObjT>
        void Setup(VariableT *var, Creator creator, Finder finder, Deleter deleter, ObjT *obj, bool valid = true);
        template<class Creator, class Finder, class Deleter, class ObjT>
        void Setup(VariableT *var, Creator creator, Finder finder, Deleter deleter, UnifiedAccess<ObjT> *obj, bool valid = true);
        template<class Getter, class Creator, class Finder, class Deleter, class ObjT>
        void Setup(Getter getter, Creator creator, Finder finder, Deleter deleter, ObjT *obj, bool valid = true);
        template<class Getter, class Creator, class Finder, class Deleter, class ObjT>
        void Setup(Getter getter, Creator creator, Finder finder, Deleter deleter, UnifiedAccess<ObjT> *obj, bool valid = true);
        void Setup(VariableT *var, CreateFuncT &&creator, FindFuncT &&finder, DeleteFuncT &&deleter, bool valid = true);
        void Setup(GetFuncT &&getter, CreateFuncT &&creator, FindFuncT &&finder, DeleteFuncT &&deleter, bool valid = true);

        ID Add(const AddArgsTupleT &add, CreateArgs && ... args);
        ID Add(const AddArgsTupleT &add, CreateArgsTupleT &create);
        FindReturnT Find(FuncID id);
        const FindReturnT Find(FuncID id) const;
        void Remove(FuncID id);

        void Edit(const VariableT &arg);
        void Edit(VariableT &&arg);
        VariableT& Get() const;

        void SetValid(bool set);
        bool IsValid() const;
        void SetEditable(bool set);
        bool IsEditable() const;

        ObjectT& ExtractObject(FindReturnT findReturn);
        const ObjectT& ExtractObject(FindReturnT findReturn) const;

        const_iterator Begin() const;
        const_iterator End() const;
        const_iterator begin() const;
        const_iterator end() const;
    };

    template<class T, class Object, class FindReturn, class IDPass, class IDFuncPass, class AddArgsPack, class... CreateArgs>
    UnifiedAccessHandlerList<T, Object, FindReturn, IDPass, IDFuncPass, AddArgsPack, CreateArgs...>::U::U()
    {}

    template<class T, class Object, class FindReturn, class IDPass, class IDFuncPass, class AddArgsPack, class... CreateArgs>
    UnifiedAccessHandlerList<T, Object, FindReturn, IDPass, IDFuncPass, AddArgsPack, CreateArgs...>::U::~U()
    {}

    template<class T, class Object, class FindReturn, class IDPass, class IDFuncPass, class AddArgsPack, class... CreateArgs>
    void UnifiedAccessHandlerList<T, Object, FindReturn, IDPass, IDFuncPass, AddArgsPack, CreateArgs...>::CopyU(const UnifiedAccessHandlerList &arg)
    {
        switch (arg.type)
        {
        case Type::VAR:
            new (&u.var) VariableT*(arg.u.var);
            break;
        case Type::FUNC:
            new (&u.getFunc) GetFuncT(arg.u.getFunc);
            break;
        }
    }

    template<class T, class Object, class FindReturn, class IDPass, class IDFuncPass, class AddArgsPack, class... CreateArgs>
    void UnifiedAccessHandlerList<T, Object, FindReturn, IDPass, IDFuncPass, AddArgsPack, CreateArgs...>::MoveU(UnifiedAccessHandlerList &&arg)
    {
        switch (arg.type)
        {
        case Type::VAR:
            new (&u.var) VariableT*(std::move(arg.u.var));
            break;
        case Type::FUNC:
            new (&u.getFunc) GetFuncT(std::move(arg.u.getFunc));
            break;
        }
    }

    template<class T, class Object, class FindReturn, class IDPass, class IDFuncPass, class AddArgsPack, class... CreateArgs>
    void UnifiedAccessHandlerList<T, Object, FindReturn, IDPass, IDFuncPass, AddArgsPack, CreateArgs...>::SetupCommonVariable(VariableT *var, CreateFuncT &&createFunc, FindFuncT &&findFunc, DeleteFuncT &&removeFunc)
    {
        if (!IsValid())
        {
            type = Type::NONE;
            return;
        }

        new (&u.var) VariableT*(var);
        this->createFunc = std::move(createFunc);
        this->findFunc = std::move(findFunc);
        this->removeFunc = std::move(removeFunc);
        type = Type::VAR;
    }

    template<class T, class Object, class FindReturn, class IDPass, class IDFuncPass, class AddArgsPack, class... CreateArgs>
    void UnifiedAccessHandlerList<T, Object, FindReturn, IDPass, IDFuncPass, AddArgsPack, CreateArgs...>::SetupCommonFunction(GetFuncT &&getFunc, CreateFuncT &&createFunc, FindFuncT &&findFunc, DeleteFuncT &&removeFunc)
    {
        if (!IsValid())
        {
            type = Type::NONE;
            return;
        }

        new (&u.getFunc) GetFuncT(std::move(getFunc));
        this->createFunc = std::move(createFunc);
        this->findFunc = std::move(findFunc);
        this->removeFunc = std::move(removeFunc);
        type = Type::FUNC;
    }

    template<class T, class Object, class FindReturn, class IDPass, class IDFuncPass, class AddArgsPack, class... CreateArgs>
    typename UnifiedAccessHandlerList<T, Object, FindReturn, IDPass, IDFuncPass, AddArgsPack, CreateArgs...>::FindReturnT UnifiedAccessHandlerList<T, Object, FindReturn, IDPass, IDFuncPass, AddArgsPack, CreateArgs...>::GetInvalidObjectReturn() const
    {
        return GetInvalidObjectReturnImpl();
    }

    template<class T, class Object, class FindReturn, class IDPass, class IDFuncPass, class AddArgsPack, class... CreateArgs>
    typename UnifiedAccessHandlerList<T, Object, FindReturn, IDPass, IDFuncPass, AddArgsPack, CreateArgs...>::ID UnifiedAccessHandlerList<T, Object, FindReturn, IDPass, IDFuncPass, AddArgsPack, CreateArgs...>::GetInvalidIDReturn() const
    {
        return GetInvalidIDReturnImpl();
    }

    template<class T, class Object, class FindReturn, class IDPass, class IDFuncPass, class AddArgsPack, class... CreateArgs>
    UnifiedAccessHandlerList<T, Object, FindReturn, IDPass, IDFuncPass, AddArgsPack, CreateArgs...>::UnifiedAccessHandlerList() : valid(false), editable(true), type(Type::NONE)
    {}

    template<class T, class Object, class FindReturn, class IDPass, class IDFuncPass, class AddArgsPack, class... CreateArgs>
    UnifiedAccessHandlerList<T, Object, FindReturn, IDPass, IDFuncPass, AddArgsPack, CreateArgs...>::UnifiedAccessHandlerList(const UnifiedAccessHandlerList &arg) : valid(arg.valid), editable(arg.editable), createFunc(arg.createFunc), findFunc(arg.findFunc), removeFunc(arg.removeFunc), added(arg.added), removed(arg.removed), edited(arg.edited)
    {
        CopyU(arg);
    }

    template<class T, class Object, class FindReturn, class IDPass, class IDFuncPass, class AddArgsPack, class... CreateArgs>
    UnifiedAccessHandlerList<T, Object, FindReturn, IDPass, IDFuncPass, AddArgsPack, CreateArgs...>::UnifiedAccessHandlerList(UnifiedAccessHandlerList &&arg) : valid(std::move(arg.valid)), editable(std::move(arg.editable)), createFunc(std::move(arg.createFunc)), findFunc(std::move(arg.findFunc)), removeFunc(std::move(arg.removeFunc)), added(std::move(arg.added)), removed(std::move(arg.removed)), edited(std::move(arg.edited))
    {
        MoveU(std::move(arg));
    }

    template<class T, class Object, class FindReturn, class IDPass, class IDFuncPass, class AddArgsPack, class... CreateArgs>
    UnifiedAccessHandlerList<T, Object, FindReturn, IDPass, IDFuncPass, AddArgsPack, CreateArgs...>& UnifiedAccessHandlerList<T, Object, FindReturn, IDPass, IDFuncPass, AddArgsPack, CreateArgs...>::operator=(const UnifiedAccessHandlerList &arg)
    {
        type = arg.type;
        valid = arg.valid;
        editable = arg.editable;
        CopyU(arg);
        createFunc = arg.createFunc;
        findFunc = arg.findFunc;
        removeFunc = arg.removeFunc;
        return *this;
    }

    template<class T, class Object, class FindReturn, class IDPass, class IDFuncPass, class AddArgsPack, class... CreateArgs>
    UnifiedAccessHandlerList<T, Object, FindReturn, IDPass, IDFuncPass, AddArgsPack, CreateArgs...>& UnifiedAccessHandlerList<T, Object, FindReturn, IDPass, IDFuncPass, AddArgsPack, CreateArgs...>::operator=(UnifiedAccessHandlerList &&arg)
    {
        type = std::move(arg.type);
        valid = std::move(arg.valid);
        editable = std::move(arg.editable);
        MoveU(std::move(arg));
        createFunc = std::move(arg.createFunc);
        findFunc = std::move(arg.findFunc);
        removeFunc = std::move(arg.removeFunc);
        return *this;
    }

    template<class T, class Object, class FindReturn, class IDPass, class IDFuncPass, class AddArgsPack, class... CreateArgs>
    template<class Creator, class Finder, class Deleter, class ObjT>
    void UnifiedAccessHandlerList<T, Object, FindReturn, IDPass, IDFuncPass, AddArgsPack, CreateArgs...>::Setup(VariableT *var, Creator creator, Finder finder, Deleter deleter, ObjT *obj, bool valid)
    {
        SetValid(valid);
        SetupCommonVariable(var, ::function::CreateFunction(creator, obj), ::function::CreateFunction(finder, obj), ::function::CreateFunction(deleter, obj));
        SetupInner();
    }

    template<class T, class Object, class FindReturn, class IDPass, class IDFuncPass, class AddArgsPack, class... CreateArgs>
    template<class Creator, class Finder, class Deleter, class ObjT>
    void UnifiedAccessHandlerList<T, Object, FindReturn, IDPass, IDFuncPass, AddArgsPack, CreateArgs...>::Setup(VariableT *var, Creator creator, Finder finder, Deleter deleter, UnifiedAccess<ObjT> *obj, bool valid)
    {
        Setup(var, creator, finder, deleter, &**obj, valid);
    }

    template<class T, class Object, class FindReturn, class IDPass, class IDFuncPass, class AddArgsPack, class... CreateArgs>
    template<class Getter, class Creator, class Finder, class Deleter, class ObjT>
    void UnifiedAccessHandlerList<T, Object, FindReturn, IDPass, IDFuncPass, AddArgsPack, CreateArgs...>::Setup(Getter getter, Creator creator, Finder finder, Deleter deleter, ObjT *obj, bool valid)
    {
        SetValid(valid);
        SetupCommonFunction(::function::CreateFunction(getter, obj), ::function::CreateFunction(creator, obj), ::function::CreateFunction(finder, obj), ::function::CreateFunction(deleter, obj));
        SetupInner();
    }

    template<class T, class Object, class FindReturn, class IDPass, class IDFuncPass, class AddArgsPack, class... CreateArgs>
    template<class Getter, class Creator, class Finder, class Deleter, class ObjT>
    void UnifiedAccessHandlerList<T, Object, FindReturn, IDPass, IDFuncPass, AddArgsPack, CreateArgs...>::Setup(Getter getter, Creator creator, Finder finder, Deleter deleter, UnifiedAccess<ObjT> *obj, bool valid)
    {
        Setup(getter, creator, finder, deleter, &**obj, valid);
    }

    template<class T, class Object, class FindReturn, class IDPass, class IDFuncPass, class AddArgsPack, class... CreateArgs>
    void UnifiedAccessHandlerList<T, Object, FindReturn, IDPass, IDFuncPass, AddArgsPack, CreateArgs...>::Setup(VariableT *var, CreateFuncT &&creator, FindFuncT &&finder, DeleteFuncT &&deleter, bool valid = true)
    {
        SetValid(valid);
        SetupCommonVariable(var, std::move(creator), std::move(finder), std::move(deleter));
        SetupInner();
    }

    template<class T, class Object, class FindReturn, class IDPass, class IDFuncPass, class AddArgsPack, class... CreateArgs>
    void UnifiedAccessHandlerList<T, Object, FindReturn, IDPass, IDFuncPass, AddArgsPack, CreateArgs...>::Setup(GetFuncT &&getter, CreateFuncT &&creator, FindFuncT &&finder, DeleteFuncT &&deleter, bool valid)
    {
        SetValid(valid);
        SetupCommonFunction(std::move(getter), std::move(creator), std::move(finder), std::move(deleter));
        SetupInner();
    }

    template<class T, class Object, class FindReturn, class IDPass, class IDFuncPass, class AddArgsPack, class... CreateArgs>
    typename UnifiedAccessHandlerList<T, Object, FindReturn, IDPass, IDFuncPass, AddArgsPack, CreateArgs...>::ID UnifiedAccessHandlerList<T, Object, FindReturn, IDPass, IDFuncPass, AddArgsPack, CreateArgs...>::Add(const AddArgsTupleT &add, CreateArgs && ... args)
    {
        if (!IsValid() || !IsEditable())
            return GetInvalidIDReturnImpl();

        CreateArgsTupleT createArgsTuple(std::forward<CreateArgs>(args)...);
        if (!CanAdd(add, createArgsTuple))
            return GetInvalidIDReturnImpl();

        decltype(createFunc(std::forward<CreateArgs>(args)...)) made = createFunc(std::forward<CreateArgs>(args)...);
        OnAdd(add, createArgsTuple, made);
        added(this, made);
        return made;
    }

    template<class T, class Object, class FindReturn, class IDPass, class IDFuncPass, class AddArgsPack, class... CreateArgs>
    typename UnifiedAccessHandlerList<T, Object, FindReturn, IDPass, IDFuncPass, AddArgsPack, CreateArgs...>::ID UnifiedAccessHandlerList<T, Object, FindReturn, IDPass, IDFuncPass, AddArgsPack, CreateArgs...>::Add(const AddArgsTupleT &add, CreateArgsTupleT &create)
    {
        if (!IsValid() || !IsEditable())
            return GetInvalidIDReturnImpl();

        if (!CanAdd(add, create))
            return GetInvalidIDReturnImpl();

        auto newTuple = std::tuple_cat(add, create);
        auto made = ::function::InvokeReturn(createFunc, newTuple);
        OnAdd(add, create, made);
        added(this, made);
        return made;
    }

    template<class T, class Object, class FindReturn, class IDPass, class IDFuncPass, class AddArgsPack, class... CreateArgs>
    typename UnifiedAccessHandlerList<T, Object, FindReturn, IDPass, IDFuncPass, AddArgsPack, CreateArgs...>::FindReturnT UnifiedAccessHandlerList<T, Object, FindReturn, IDPass, IDFuncPass, AddArgsPack, CreateArgs...>::Find(FuncID id)
    {
        if (!IsValid())
            return GetInvalidObjectReturnImpl();

        return findFunc(id);
    }

    template<class T, class Object, class FindReturn, class IDPass, class IDFuncPass, class AddArgsPack, class... CreateArgs>
    typename const UnifiedAccessHandlerList<T, Object, FindReturn, IDPass, IDFuncPass, AddArgsPack, CreateArgs...>::FindReturnT UnifiedAccessHandlerList<T, Object, FindReturn, IDPass, IDFuncPass, AddArgsPack, CreateArgs...>::Find(FuncID id) const
    {
        if (!IsValid())
            return GetInvalidObjectReturnImpl();

        return findFunc(id);
    }

    template<class T, class Object, class FindReturn, class IDPass, class IDFuncPass, class AddArgsPack, class... CreateArgs>
    void UnifiedAccessHandlerList<T, Object, FindReturn, IDPass, IDFuncPass, AddArgsPack, CreateArgs...>::Remove(FuncID id)
    {
        if (!IsValid() || !IsEditable())
            return;

        PreRemove(id);
        removeFunc(id);
        OnRemove(id);
        removed(this, id);
    }

    template<class T, class Object, class FindReturn, class IDPass, class IDFuncPass, class AddArgsPack, class... CreateArgs>
    void UnifiedAccessHandlerList<T, Object, FindReturn, IDPass, IDFuncPass, AddArgsPack, CreateArgs...>::Edit(const VariableT &arg)
    {
        if (!IsValid() || !IsEditable())
            return;

        switch (type)
        {
        case Type::VAR:
            *u.varSet.var = arg;
            OnEdited();
            edited(this);
            break;
        case Type::FUNC:
            u.set.getFunc() = arg;
            OnEdited();
            edited(this);
            break;
        }
    }

    template<class T, class Object, class FindReturn, class IDPass, class IDFuncPass, class AddArgsPack, class... CreateArgs>
    void UnifiedAccessHandlerList<T, Object, FindReturn, IDPass, IDFuncPass, AddArgsPack, CreateArgs...>::Edit(VariableT &&arg)
    {
        if (!IsValid() || !IsEditable())
            return;

        switch (type)
        {
        case Type::VAR:
            *u.varSet.var = std::move(arg);
            OnEdited();
            edited(this);
            break;
        case Type::FUNC:
            u.set.getFunc() = std::move(arg);
            OnEdited();
            edited(this);
            break;
        }
    }

    template<class T, class Object, class FindReturn, class IDPass, class IDFuncPass, class AddArgsPack, class... CreateArgs>
    typename UnifiedAccessHandlerList<T, Object, FindReturn, IDPass, IDFuncPass, AddArgsPack, CreateArgs...>::VariableT& UnifiedAccessHandlerList<T, Object, FindReturn, IDPass, IDFuncPass, AddArgsPack, CreateArgs...>::Get() const
    {
        switch (type)
        {
        case Type::VAR:
            return *u.var;
        case Type::FUNC:
        default:
            return u.getFunc();
        }
    }

    template<class T, class Object, class FindReturn, class IDPass, class IDFuncPass, class AddArgsPack, class... CreateArgs>
    void UnifiedAccessHandlerList<T, Object, FindReturn, IDPass, IDFuncPass, AddArgsPack, CreateArgs...>::SetValid(bool set)
    {
        valid = set;
        OnSetEditable(set);
    }

    template<class T, class Object, class FindReturn, class IDPass, class IDFuncPass, class AddArgsPack, class... CreateArgs>
    bool UnifiedAccessHandlerList<T, Object, FindReturn, IDPass, IDFuncPass, AddArgsPack, CreateArgs...>::IsValid() const
    {
        return valid;
    }

    template<class T, class Object, class FindReturn, class IDPass, class IDFuncPass, class AddArgsPack, class... CreateArgs>
    void UnifiedAccessHandlerList<T, Object, FindReturn, IDPass, IDFuncPass, AddArgsPack, CreateArgs...>::SetEditable(bool set)
    {
        if (editable == set)
            return;

        editable = set;
        OnSetEditable(editable);
    }

    template<class T, class Object, class FindReturn, class IDPass, class IDFuncPass, class AddArgsPack, class... CreateArgs>
    bool UnifiedAccessHandlerList<T, Object, FindReturn, IDPass, IDFuncPass, AddArgsPack, CreateArgs...>::IsEditable() const
    {
        return editable;
    }

    template<class T, class Object, class FindReturn, class IDPass, class IDFuncPass, class AddArgsPack, class... CreateArgs>
    typename UnifiedAccessHandlerList<T, Object, FindReturn, IDPass, IDFuncPass, AddArgsPack, CreateArgs...>::ObjectT& UnifiedAccessHandlerList<T, Object, FindReturn, IDPass, IDFuncPass, AddArgsPack, CreateArgs...>::ExtractObject(FindReturnT findReturn)
    {
        return ExtractObjectImpl(findReturn);
    }

    template<class T, class Object, class FindReturn, class IDPass, class IDFuncPass, class AddArgsPack, class... CreateArgs>
    typename const UnifiedAccessHandlerList<T, Object, FindReturn, IDPass, IDFuncPass, AddArgsPack, CreateArgs...>::ObjectT& UnifiedAccessHandlerList<T, Object, FindReturn, IDPass, IDFuncPass, AddArgsPack, CreateArgs...>::ExtractObject(FindReturnT findReturn) const
    {
        return const_cast<UnifiedAccessHandlerList*>(this)->ExtractObjectImpl(findReturn);
    }

    template<class T, class Object, class FindReturn, class IDPass, class IDFuncPass, class AddArgsPack, class... CreateArgs>
    typename UnifiedAccessHandlerList<T, Object, FindReturn, IDPass, IDFuncPass, AddArgsPack, CreateArgs...>::const_iterator UnifiedAccessHandlerList<T, Object, FindReturn, IDPass, IDFuncPass, AddArgsPack, CreateArgs...>::Begin() const
    {
        return Get().begin();
    }

    template<class T, class Object, class FindReturn, class IDPass, class IDFuncPass, class AddArgsPack, class... CreateArgs>
    typename UnifiedAccessHandlerList<T, Object, FindReturn, IDPass, IDFuncPass, AddArgsPack, CreateArgs...>::const_iterator UnifiedAccessHandlerList<T, Object, FindReturn, IDPass, IDFuncPass, AddArgsPack, CreateArgs...>::End() const
    {
        return Get().end();
    }

    template<class T, class Object, class FindReturn, class IDPass, class IDFuncPass, class AddArgsPack, class... CreateArgs>
    typename UnifiedAccessHandlerList<T, Object, FindReturn, IDPass, IDFuncPass, AddArgsPack, CreateArgs...>::const_iterator UnifiedAccessHandlerList<T, Object, FindReturn, IDPass, IDFuncPass, AddArgsPack, CreateArgs...>::begin() const
    {
        return Begin();
    }

    template<class T, class Object, class FindReturn, class IDPass, class IDFuncPass, class AddArgsPack, class... CreateArgs>
    typename UnifiedAccessHandlerList<T, Object, FindReturn, IDPass, IDFuncPass, AddArgsPack, CreateArgs...>::const_iterator UnifiedAccessHandlerList<T, Object, FindReturn, IDPass, IDFuncPass, AddArgsPack, CreateArgs...>::end() const
    {
        return End();
    }

    template<class T, class Object, class FindReturn, class IDPass, class IDFuncPass>
    class UnifiedAccessHandlerStaticList : public UnifiedAccessHandlerBase
    {
    public:
        typedef T VariableT;
        typedef Object ObjectT;
        typedef FindReturn FindReturnT;
        typedef IDPass ID;
        typedef IDFuncPass FuncID;

        typedef typename std::remove_const<typename std::remove_reference<ID>::type>::type IDStoreT;
        typedef std::vector<IDStoreT> IDVector;
    private:
        typedef ::function::Function<VariableT&> GetFuncT;
        typedef ::function::Function<FindReturnT, FuncID> FindFuncT;

        enum class Type
        {
            NONE,
            VAR,
            FUNC
        };

        union U
        {
            VariableT *var;
            GetFuncT getFunc;
            U();
            ~U();
        };
    private:
        bool valid;

        Type type;
        U u;

        FindFuncT findFunc;

        void CopyU(const UnifiedAccessHandlerStaticList &arg);
        void MoveU(UnifiedAccessHandlerStaticList &&arg);

        void SetupCommon(VariableT *var, FindFuncT &&findFunc);
        void SetupCommon(GetFuncT &&getFunc, FindFuncT &&findFunc);

        virtual void SetupInner() {}
        virtual void SetupIDs(IDVector ids) = 0;

        virtual FindReturnT GetInvalidObjectReturnImpl() const = 0;
    public:
        UnifiedAccessHandlerStaticList();
        UnifiedAccessHandlerStaticList(const UnifiedAccessHandlerStaticList &arg);
        UnifiedAccessHandlerStaticList(UnifiedAccessHandlerStaticList &&arg);
        UnifiedAccessHandlerStaticList& operator=(const UnifiedAccessHandlerStaticList &arg);
        UnifiedAccessHandlerStaticList& operator=(UnifiedAccessHandlerStaticList &&arg);
        virtual ~UnifiedAccessHandlerStaticList() = 0 {}

        template<class Finder>
        void Setup(VariableT *var, Finder finder, IDVector &&ids, bool valid = true);
        template<class Finder, class ObjT>
        void Setup(VariableT *var, Finder finder, ObjT *obj, IDVector &&ids, bool valid = true);
        template<class Finder, class ObjT>
        void Setup(VariableT *var, Finder finder, UnifiedAccess<ObjT> *obj, IDVector &&ids, bool valid = true);
        template<class Getter, class Finder>
        void Setup(Getter getter, Finder finder, IDVector &&ids, bool valid = true);
        template<class Getter, class Finder, class ObjT>
        void Setup(Getter getter, Finder finder, ObjT *obj, IDVector &&ids, bool valid = true);
        template<class Getter, class Finder, class ObjT>
        void Setup(Getter getter, Finder finder, UnifiedAccess<ObjT> *obj, IDVector &&ids, bool valid = true);
        void Setup(VariableT *var, FindFuncT &&finder, IDVector &&ids, bool valid = true);
        void Setup(GetFuncT &&getter, FindFuncT &&finder, IDVector &&ids, bool valid = true);

        FindReturnT Find(FuncID id);
        const FindReturnT Find(FuncID id) const;

        VariableT& Get() const;

        void SetValid(bool set);
        bool IsValid() const;
    };

    template<class T, class Object, class FindReturn, class IDPass, class IDFuncPass>
    UnifiedAccessHandlerStaticList<T, Object, FindReturn, IDPass, IDFuncPass>::U::U()
    {}

    template<class T, class Object, class FindReturn, class IDPass, class IDFuncPass>
    UnifiedAccessHandlerStaticList<T, Object, FindReturn, IDPass, IDFuncPass>::U::~U()
    {}

    template<class T, class Object, class FindReturn, class IDPass, class IDFuncPass>
    void UnifiedAccessHandlerStaticList<T, Object, FindReturn, IDPass, IDFuncPass>::CopyU(const UnifiedAccessHandlerStaticList &arg)
    {
        switch (arg.type)
        {
        case Type::VAR:
            u.var = arg.u.var;
            break;
        case Type::FUNC:
            u.getFunc = arg.u.getFunc;
            break;
        }
    }

    template<class T, class Object, class FindReturn, class IDPass, class IDFuncPass>
    void UnifiedAccessHandlerStaticList<T, Object, FindReturn, IDPass, IDFuncPass>::MoveU(UnifiedAccessHandlerStaticList &&arg)
    {
        switch (arg.type)
        {
        case Type::VAR:
            u.var = std::move(arg.u.var);
            break;
        case Type::FUNC:
            u.getFunc = std::move(arg.u.getFunc);
            break;
        }
    }

    template<class T, class Object, class FindReturn, class IDPass, class IDFuncPass>
    void UnifiedAccessHandlerStaticList<T, Object, FindReturn, IDPass, IDFuncPass>::SetupCommon(VariableT *var, FindFuncT &&findFunc)
    {
        if (!IsValid())
        {
            type = Type::NONE;
            return;
        }

        u.var = var;
        this->findFunc = std::move(findFunc);
        type = Type::VAR;
    }

    template<class T, class Object, class FindReturn, class IDPass, class IDFuncPass>
    void UnifiedAccessHandlerStaticList<T, Object, FindReturn, IDPass, IDFuncPass>::SetupCommon(GetFuncT &&getFunc, FindFuncT &&findFunc)
    {
        if (!IsValid())
        {
            type = Type::NONE;
            return;
        }

        u.getFunc = std::move(getFunc);
        this->findFunc = std::move(findFunc);
        type = Type::VAR;
    }

    template<class T, class Object, class FindReturn, class IDPass, class IDFuncPass>
    UnifiedAccessHandlerStaticList<T, Object, FindReturn, IDPass, IDFuncPass>::UnifiedAccessHandlerStaticList() : type(Type::NONE), valid(false)
    {}

    template<class T, class Object, class FindReturn, class IDPass, class IDFuncPass>
    UnifiedAccessHandlerStaticList<T, Object, FindReturn, IDPass, IDFuncPass>::UnifiedAccessHandlerStaticList(const UnifiedAccessHandlerStaticList &arg) : type(arg.type), valid(arg.valid), findFunc(arg.findFunc)
    {
        CopyU(arg);
    }

    template<class T, class Object, class FindReturn, class IDPass, class IDFuncPass>
    UnifiedAccessHandlerStaticList<T, Object, FindReturn, IDPass, IDFuncPass>::UnifiedAccessHandlerStaticList(UnifiedAccessHandlerStaticList &&arg) : type(std::move(arg.type)), valid(std::move(arg.valid)), findFunc(std::move(arg.findFunc))
    {
        MoveU(std::move(arg));
    }

    template<class T, class Object, class FindReturn, class IDPass, class IDFuncPass>
    UnifiedAccessHandlerStaticList<T, Object, FindReturn, IDPass, IDFuncPass>& UnifiedAccessHandlerStaticList<T, Object, FindReturn, IDPass, IDFuncPass>::operator=(const UnifiedAccessHandlerStaticList &arg)
    {
        type = arg.type;
        valid = arg.valid;
        CopyU(arg);
        findFunc = arg.findFunc;
        return *this;
    }

    template<class T, class Object, class FindReturn, class IDPass, class IDFuncPass>
    UnifiedAccessHandlerStaticList<T, Object, FindReturn, IDPass, IDFuncPass>& UnifiedAccessHandlerStaticList<T, Object, FindReturn, IDPass, IDFuncPass>::operator=(UnifiedAccessHandlerStaticList &&arg)
    {
        type = std::move(arg.type);
        valid = std::move(arg.valid);
        MoveU(std::move(arg));
        findFunc = std::move(arg.findFunc);
        return *this;
    }

    template<class T, class Object, class FindReturn, class IDPass, class IDFuncPass>
    template<class Finder>
    void UnifiedAccessHandlerStaticList<T, Object, FindReturn, IDPass, IDFuncPass>::Setup(VariableT *var, Finder finder, IDVector &&ids, bool valid)
    {
        SetValid(valid);
        SetupCommon(var, ::function::CreateFunction(finder));
        SetupIDs(std::move(ids));
        SetupInner();
    }

    template<class T, class Object, class FindReturn, class IDPass, class IDFuncPass>
    template<class Finder, class ObjT>
    void UnifiedAccessHandlerStaticList<T, Object, FindReturn, IDPass, IDFuncPass>::Setup(VariableT *var, Finder finder, ObjT *obj, IDVector &&ids, bool valid)
    {
        SetValid(valid);
        SetupCommon(var, ::function::CreateFunction(finder, obj));
        SetupIDs(std::move(ids));
        SetupInner();
    }

    template<class T, class Object, class FindReturn, class IDPass, class IDFuncPass>
    template<class Finder, class ObjT>
    void UnifiedAccessHandlerStaticList<T, Object, FindReturn, IDPass, IDFuncPass>::Setup(VariableT *var, Finder finder, UnifiedAccess<ObjT> *obj, IDVector &&ids, bool valid)
    {
        Setup(var, finder, &**obj, std::move(ids), valid);
    }

    template<class T, class Object, class FindReturn, class IDPass, class IDFuncPass>
    template<class Getter, class Finder>
    void UnifiedAccessHandlerStaticList<T, Object, FindReturn, IDPass, IDFuncPass>::Setup(Getter getter, Finder finder, IDVector &&ids, bool valid)
    {
        SetValid(valid);
        SetupCommon(::function::CreateFunction(getter), ::function::CreateFunction(finder));
        SetupIDs(std::move(ids));
        SetupInner();
    }

    template<class T, class Object, class FindReturn, class IDPass, class IDFuncPass>
    template<class Getter, class Finder, class ObjT>
    void UnifiedAccessHandlerStaticList<T, Object, FindReturn, IDPass, IDFuncPass>::Setup(Getter getter, Finder finder, ObjT *obj, IDVector &&ids, bool valid)
    {
        SetValid(valid);
        SetupCommon(::function::CreateFunction(getter, obj), ::function::CreateFunction(finder, obj));
        SetupIDs(std::move(ids));
        SetupInner();
    }

    template<class T, class Object, class FindReturn, class IDPass, class IDFuncPass>
    template<class Getter, class Finder, class ObjT>
    void UnifiedAccessHandlerStaticList<T, Object, FindReturn, IDPass, IDFuncPass>::Setup(Getter getter, Finder finder, UnifiedAccess<ObjT> *obj, IDVector &&ids, bool valid)
    {
        Setup(getter, finder, &**obj, std::move(ids));
    }

    template<class T, class Object, class FindReturn, class IDPass, class IDFuncPass>
    void UnifiedAccessHandlerStaticList<T, Object, FindReturn, IDPass, IDFuncPass>::Setup(VariableT *var, FindFuncT &&finder, IDVector &&ids, bool valid)
    {
        SetValid(valid);
        SetupCommon(var, std::move(finder), std::move(ids));
        SetupIDs(std::move(ids));
        SetupInner();
    }

    template<class T, class Object, class FindReturn, class IDPass, class IDFuncPass>
    void UnifiedAccessHandlerStaticList<T, Object, FindReturn, IDPass, IDFuncPass>::Setup(GetFuncT &&getter, FindFuncT &&finder, IDVector &&ids, bool valid)
    {
        SetValid(valid);
        SetupCommon(std::move(getter), std::move(finder));
        SetupIDs(std::move(ids));
        SetupInner();
    }

    template<class T, class Object, class FindReturn, class IDPass, class IDFuncPass>
    typename UnifiedAccessHandlerStaticList<T, Object, FindReturn, IDPass, IDFuncPass>::FindReturnT UnifiedAccessHandlerStaticList<T, Object, FindReturn, IDPass, IDFuncPass>::Find(FuncID id)
    {
        if (!IsValid())
            return GetInvalidObjectReturnImpl();

        return findFunc(id);
    }

    template<class T, class Object, class FindReturn, class IDPass, class IDFuncPass>
    typename const UnifiedAccessHandlerStaticList<T, Object, FindReturn, IDPass, IDFuncPass>::FindReturnT UnifiedAccessHandlerStaticList<T, Object, FindReturn, IDPass, IDFuncPass>::Find(FuncID id) const
    {
        if (!IsValid())
            return GetInvalidObjectReturnImpl();

        return findFunc(id);
    }

    template<class T, class Object, class FindReturn, class IDPass, class IDFuncPass>
    typename UnifiedAccessHandlerStaticList<T, Object, FindReturn, IDPass, IDFuncPass>::VariableT& UnifiedAccessHandlerStaticList<T, Object, FindReturn, IDPass, IDFuncPass>::Get() const
    {
        switch (type)
        {
        case Type::VAR:
            return *u.var;
        case Type::FUNC:
        default:
            return u.getFunc();
        }
    }

    template<class T, class Object, class FindReturn, class IDPass, class IDFuncPass>
    void UnifiedAccessHandlerStaticList<T, Object, FindReturn, IDPass, IDFuncPass>::SetValid(bool set)
    {
        valid = set;
    }

    template<class T, class Object, class FindReturn, class IDPass, class IDFuncPass>
    bool UnifiedAccessHandlerStaticList<T, Object, FindReturn, IDPass, IDFuncPass>::IsValid() const
    {
        return valid;
    }
    */
}