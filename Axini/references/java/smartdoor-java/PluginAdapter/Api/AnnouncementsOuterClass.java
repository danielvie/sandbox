// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: announcements.proto

package PluginAdapter.Api;

public final class AnnouncementsOuterClass {
  private AnnouncementsOuterClass() {}
  public static void registerAllExtensions(
      com.google.protobuf.ExtensionRegistryLite registry) {
  }

  public static void registerAllExtensions(
      com.google.protobuf.ExtensionRegistry registry) {
    registerAllExtensions(
        (com.google.protobuf.ExtensionRegistryLite) registry);
  }
  public interface AnnouncementsOrBuilder extends
      // @@protoc_insertion_point(interface_extends:PluginAdapter.Api.Announcements)
      com.google.protobuf.MessageOrBuilder {

    /**
     * <code>repeated .PluginAdapter.Api.Announcement announcements = 1;</code>
     */
    java.util.List<PluginAdapter.Api.AnnouncementOuterClass.Announcement> 
        getAnnouncementsList();
    /**
     * <code>repeated .PluginAdapter.Api.Announcement announcements = 1;</code>
     */
    PluginAdapter.Api.AnnouncementOuterClass.Announcement getAnnouncements(int index);
    /**
     * <code>repeated .PluginAdapter.Api.Announcement announcements = 1;</code>
     */
    int getAnnouncementsCount();
    /**
     * <code>repeated .PluginAdapter.Api.Announcement announcements = 1;</code>
     */
    java.util.List<? extends PluginAdapter.Api.AnnouncementOuterClass.AnnouncementOrBuilder> 
        getAnnouncementsOrBuilderList();
    /**
     * <code>repeated .PluginAdapter.Api.Announcement announcements = 1;</code>
     */
    PluginAdapter.Api.AnnouncementOuterClass.AnnouncementOrBuilder getAnnouncementsOrBuilder(
        int index);
  }
  /**
   * Protobuf type {@code PluginAdapter.Api.Announcements}
   */
  public static final class Announcements extends
      com.google.protobuf.GeneratedMessageV3 implements
      // @@protoc_insertion_point(message_implements:PluginAdapter.Api.Announcements)
      AnnouncementsOrBuilder {
  private static final long serialVersionUID = 0L;
    // Use Announcements.newBuilder() to construct.
    private Announcements(com.google.protobuf.GeneratedMessageV3.Builder<?> builder) {
      super(builder);
    }
    private Announcements() {
      announcements_ = java.util.Collections.emptyList();
    }

    @java.lang.Override
    @SuppressWarnings({"unused"})
    protected java.lang.Object newInstance(
        UnusedPrivateParameter unused) {
      return new Announcements();
    }

    @java.lang.Override
    public final com.google.protobuf.UnknownFieldSet
    getUnknownFields() {
      return this.unknownFields;
    }
    public static final com.google.protobuf.Descriptors.Descriptor
        getDescriptor() {
      return PluginAdapter.Api.AnnouncementsOuterClass.internal_static_PluginAdapter_Api_Announcements_descriptor;
    }

    @java.lang.Override
    protected com.google.protobuf.GeneratedMessageV3.FieldAccessorTable
        internalGetFieldAccessorTable() {
      return PluginAdapter.Api.AnnouncementsOuterClass.internal_static_PluginAdapter_Api_Announcements_fieldAccessorTable
          .ensureFieldAccessorsInitialized(
              PluginAdapter.Api.AnnouncementsOuterClass.Announcements.class, PluginAdapter.Api.AnnouncementsOuterClass.Announcements.Builder.class);
    }

    public static final int ANNOUNCEMENTS_FIELD_NUMBER = 1;
    @SuppressWarnings("serial")
    private java.util.List<PluginAdapter.Api.AnnouncementOuterClass.Announcement> announcements_;
    /**
     * <code>repeated .PluginAdapter.Api.Announcement announcements = 1;</code>
     */
    @java.lang.Override
    public java.util.List<PluginAdapter.Api.AnnouncementOuterClass.Announcement> getAnnouncementsList() {
      return announcements_;
    }
    /**
     * <code>repeated .PluginAdapter.Api.Announcement announcements = 1;</code>
     */
    @java.lang.Override
    public java.util.List<? extends PluginAdapter.Api.AnnouncementOuterClass.AnnouncementOrBuilder> 
        getAnnouncementsOrBuilderList() {
      return announcements_;
    }
    /**
     * <code>repeated .PluginAdapter.Api.Announcement announcements = 1;</code>
     */
    @java.lang.Override
    public int getAnnouncementsCount() {
      return announcements_.size();
    }
    /**
     * <code>repeated .PluginAdapter.Api.Announcement announcements = 1;</code>
     */
    @java.lang.Override
    public PluginAdapter.Api.AnnouncementOuterClass.Announcement getAnnouncements(int index) {
      return announcements_.get(index);
    }
    /**
     * <code>repeated .PluginAdapter.Api.Announcement announcements = 1;</code>
     */
    @java.lang.Override
    public PluginAdapter.Api.AnnouncementOuterClass.AnnouncementOrBuilder getAnnouncementsOrBuilder(
        int index) {
      return announcements_.get(index);
    }

    private byte memoizedIsInitialized = -1;
    @java.lang.Override
    public final boolean isInitialized() {
      byte isInitialized = memoizedIsInitialized;
      if (isInitialized == 1) return true;
      if (isInitialized == 0) return false;

      memoizedIsInitialized = 1;
      return true;
    }

    @java.lang.Override
    public void writeTo(com.google.protobuf.CodedOutputStream output)
                        throws java.io.IOException {
      for (int i = 0; i < announcements_.size(); i++) {
        output.writeMessage(1, announcements_.get(i));
      }
      getUnknownFields().writeTo(output);
    }

    @java.lang.Override
    public int getSerializedSize() {
      int size = memoizedSize;
      if (size != -1) return size;

      size = 0;
      for (int i = 0; i < announcements_.size(); i++) {
        size += com.google.protobuf.CodedOutputStream
          .computeMessageSize(1, announcements_.get(i));
      }
      size += getUnknownFields().getSerializedSize();
      memoizedSize = size;
      return size;
    }

    @java.lang.Override
    public boolean equals(final java.lang.Object obj) {
      if (obj == this) {
       return true;
      }
      if (!(obj instanceof PluginAdapter.Api.AnnouncementsOuterClass.Announcements)) {
        return super.equals(obj);
      }
      PluginAdapter.Api.AnnouncementsOuterClass.Announcements other = (PluginAdapter.Api.AnnouncementsOuterClass.Announcements) obj;

      if (!getAnnouncementsList()
          .equals(other.getAnnouncementsList())) return false;
      if (!getUnknownFields().equals(other.getUnknownFields())) return false;
      return true;
    }

    @java.lang.Override
    public int hashCode() {
      if (memoizedHashCode != 0) {
        return memoizedHashCode;
      }
      int hash = 41;
      hash = (19 * hash) + getDescriptor().hashCode();
      if (getAnnouncementsCount() > 0) {
        hash = (37 * hash) + ANNOUNCEMENTS_FIELD_NUMBER;
        hash = (53 * hash) + getAnnouncementsList().hashCode();
      }
      hash = (29 * hash) + getUnknownFields().hashCode();
      memoizedHashCode = hash;
      return hash;
    }

    public static PluginAdapter.Api.AnnouncementsOuterClass.Announcements parseFrom(
        java.nio.ByteBuffer data)
        throws com.google.protobuf.InvalidProtocolBufferException {
      return PARSER.parseFrom(data);
    }
    public static PluginAdapter.Api.AnnouncementsOuterClass.Announcements parseFrom(
        java.nio.ByteBuffer data,
        com.google.protobuf.ExtensionRegistryLite extensionRegistry)
        throws com.google.protobuf.InvalidProtocolBufferException {
      return PARSER.parseFrom(data, extensionRegistry);
    }
    public static PluginAdapter.Api.AnnouncementsOuterClass.Announcements parseFrom(
        com.google.protobuf.ByteString data)
        throws com.google.protobuf.InvalidProtocolBufferException {
      return PARSER.parseFrom(data);
    }
    public static PluginAdapter.Api.AnnouncementsOuterClass.Announcements parseFrom(
        com.google.protobuf.ByteString data,
        com.google.protobuf.ExtensionRegistryLite extensionRegistry)
        throws com.google.protobuf.InvalidProtocolBufferException {
      return PARSER.parseFrom(data, extensionRegistry);
    }
    public static PluginAdapter.Api.AnnouncementsOuterClass.Announcements parseFrom(byte[] data)
        throws com.google.protobuf.InvalidProtocolBufferException {
      return PARSER.parseFrom(data);
    }
    public static PluginAdapter.Api.AnnouncementsOuterClass.Announcements parseFrom(
        byte[] data,
        com.google.protobuf.ExtensionRegistryLite extensionRegistry)
        throws com.google.protobuf.InvalidProtocolBufferException {
      return PARSER.parseFrom(data, extensionRegistry);
    }
    public static PluginAdapter.Api.AnnouncementsOuterClass.Announcements parseFrom(java.io.InputStream input)
        throws java.io.IOException {
      return com.google.protobuf.GeneratedMessageV3
          .parseWithIOException(PARSER, input);
    }
    public static PluginAdapter.Api.AnnouncementsOuterClass.Announcements parseFrom(
        java.io.InputStream input,
        com.google.protobuf.ExtensionRegistryLite extensionRegistry)
        throws java.io.IOException {
      return com.google.protobuf.GeneratedMessageV3
          .parseWithIOException(PARSER, input, extensionRegistry);
    }
    public static PluginAdapter.Api.AnnouncementsOuterClass.Announcements parseDelimitedFrom(java.io.InputStream input)
        throws java.io.IOException {
      return com.google.protobuf.GeneratedMessageV3
          .parseDelimitedWithIOException(PARSER, input);
    }
    public static PluginAdapter.Api.AnnouncementsOuterClass.Announcements parseDelimitedFrom(
        java.io.InputStream input,
        com.google.protobuf.ExtensionRegistryLite extensionRegistry)
        throws java.io.IOException {
      return com.google.protobuf.GeneratedMessageV3
          .parseDelimitedWithIOException(PARSER, input, extensionRegistry);
    }
    public static PluginAdapter.Api.AnnouncementsOuterClass.Announcements parseFrom(
        com.google.protobuf.CodedInputStream input)
        throws java.io.IOException {
      return com.google.protobuf.GeneratedMessageV3
          .parseWithIOException(PARSER, input);
    }
    public static PluginAdapter.Api.AnnouncementsOuterClass.Announcements parseFrom(
        com.google.protobuf.CodedInputStream input,
        com.google.protobuf.ExtensionRegistryLite extensionRegistry)
        throws java.io.IOException {
      return com.google.protobuf.GeneratedMessageV3
          .parseWithIOException(PARSER, input, extensionRegistry);
    }

    @java.lang.Override
    public Builder newBuilderForType() { return newBuilder(); }
    public static Builder newBuilder() {
      return DEFAULT_INSTANCE.toBuilder();
    }
    public static Builder newBuilder(PluginAdapter.Api.AnnouncementsOuterClass.Announcements prototype) {
      return DEFAULT_INSTANCE.toBuilder().mergeFrom(prototype);
    }
    @java.lang.Override
    public Builder toBuilder() {
      return this == DEFAULT_INSTANCE
          ? new Builder() : new Builder().mergeFrom(this);
    }

    @java.lang.Override
    protected Builder newBuilderForType(
        com.google.protobuf.GeneratedMessageV3.BuilderParent parent) {
      Builder builder = new Builder(parent);
      return builder;
    }
    /**
     * Protobuf type {@code PluginAdapter.Api.Announcements}
     */
    public static final class Builder extends
        com.google.protobuf.GeneratedMessageV3.Builder<Builder> implements
        // @@protoc_insertion_point(builder_implements:PluginAdapter.Api.Announcements)
        PluginAdapter.Api.AnnouncementsOuterClass.AnnouncementsOrBuilder {
      public static final com.google.protobuf.Descriptors.Descriptor
          getDescriptor() {
        return PluginAdapter.Api.AnnouncementsOuterClass.internal_static_PluginAdapter_Api_Announcements_descriptor;
      }

      @java.lang.Override
      protected com.google.protobuf.GeneratedMessageV3.FieldAccessorTable
          internalGetFieldAccessorTable() {
        return PluginAdapter.Api.AnnouncementsOuterClass.internal_static_PluginAdapter_Api_Announcements_fieldAccessorTable
            .ensureFieldAccessorsInitialized(
                PluginAdapter.Api.AnnouncementsOuterClass.Announcements.class, PluginAdapter.Api.AnnouncementsOuterClass.Announcements.Builder.class);
      }

      // Construct using PluginAdapter.Api.AnnouncementsOuterClass.Announcements.newBuilder()
      private Builder() {

      }

      private Builder(
          com.google.protobuf.GeneratedMessageV3.BuilderParent parent) {
        super(parent);

      }
      @java.lang.Override
      public Builder clear() {
        super.clear();
        bitField0_ = 0;
        if (announcementsBuilder_ == null) {
          announcements_ = java.util.Collections.emptyList();
        } else {
          announcements_ = null;
          announcementsBuilder_.clear();
        }
        bitField0_ = (bitField0_ & ~0x00000001);
        return this;
      }

      @java.lang.Override
      public com.google.protobuf.Descriptors.Descriptor
          getDescriptorForType() {
        return PluginAdapter.Api.AnnouncementsOuterClass.internal_static_PluginAdapter_Api_Announcements_descriptor;
      }

      @java.lang.Override
      public PluginAdapter.Api.AnnouncementsOuterClass.Announcements getDefaultInstanceForType() {
        return PluginAdapter.Api.AnnouncementsOuterClass.Announcements.getDefaultInstance();
      }

      @java.lang.Override
      public PluginAdapter.Api.AnnouncementsOuterClass.Announcements build() {
        PluginAdapter.Api.AnnouncementsOuterClass.Announcements result = buildPartial();
        if (!result.isInitialized()) {
          throw newUninitializedMessageException(result);
        }
        return result;
      }

      @java.lang.Override
      public PluginAdapter.Api.AnnouncementsOuterClass.Announcements buildPartial() {
        PluginAdapter.Api.AnnouncementsOuterClass.Announcements result = new PluginAdapter.Api.AnnouncementsOuterClass.Announcements(this);
        buildPartialRepeatedFields(result);
        if (bitField0_ != 0) { buildPartial0(result); }
        onBuilt();
        return result;
      }

      private void buildPartialRepeatedFields(PluginAdapter.Api.AnnouncementsOuterClass.Announcements result) {
        if (announcementsBuilder_ == null) {
          if (((bitField0_ & 0x00000001) != 0)) {
            announcements_ = java.util.Collections.unmodifiableList(announcements_);
            bitField0_ = (bitField0_ & ~0x00000001);
          }
          result.announcements_ = announcements_;
        } else {
          result.announcements_ = announcementsBuilder_.build();
        }
      }

      private void buildPartial0(PluginAdapter.Api.AnnouncementsOuterClass.Announcements result) {
        int from_bitField0_ = bitField0_;
      }

      @java.lang.Override
      public Builder clone() {
        return super.clone();
      }
      @java.lang.Override
      public Builder setField(
          com.google.protobuf.Descriptors.FieldDescriptor field,
          java.lang.Object value) {
        return super.setField(field, value);
      }
      @java.lang.Override
      public Builder clearField(
          com.google.protobuf.Descriptors.FieldDescriptor field) {
        return super.clearField(field);
      }
      @java.lang.Override
      public Builder clearOneof(
          com.google.protobuf.Descriptors.OneofDescriptor oneof) {
        return super.clearOneof(oneof);
      }
      @java.lang.Override
      public Builder setRepeatedField(
          com.google.protobuf.Descriptors.FieldDescriptor field,
          int index, java.lang.Object value) {
        return super.setRepeatedField(field, index, value);
      }
      @java.lang.Override
      public Builder addRepeatedField(
          com.google.protobuf.Descriptors.FieldDescriptor field,
          java.lang.Object value) {
        return super.addRepeatedField(field, value);
      }
      @java.lang.Override
      public Builder mergeFrom(com.google.protobuf.Message other) {
        if (other instanceof PluginAdapter.Api.AnnouncementsOuterClass.Announcements) {
          return mergeFrom((PluginAdapter.Api.AnnouncementsOuterClass.Announcements)other);
        } else {
          super.mergeFrom(other);
          return this;
        }
      }

      public Builder mergeFrom(PluginAdapter.Api.AnnouncementsOuterClass.Announcements other) {
        if (other == PluginAdapter.Api.AnnouncementsOuterClass.Announcements.getDefaultInstance()) return this;
        if (announcementsBuilder_ == null) {
          if (!other.announcements_.isEmpty()) {
            if (announcements_.isEmpty()) {
              announcements_ = other.announcements_;
              bitField0_ = (bitField0_ & ~0x00000001);
            } else {
              ensureAnnouncementsIsMutable();
              announcements_.addAll(other.announcements_);
            }
            onChanged();
          }
        } else {
          if (!other.announcements_.isEmpty()) {
            if (announcementsBuilder_.isEmpty()) {
              announcementsBuilder_.dispose();
              announcementsBuilder_ = null;
              announcements_ = other.announcements_;
              bitField0_ = (bitField0_ & ~0x00000001);
              announcementsBuilder_ = 
                com.google.protobuf.GeneratedMessageV3.alwaysUseFieldBuilders ?
                   getAnnouncementsFieldBuilder() : null;
            } else {
              announcementsBuilder_.addAllMessages(other.announcements_);
            }
          }
        }
        this.mergeUnknownFields(other.getUnknownFields());
        onChanged();
        return this;
      }

      @java.lang.Override
      public final boolean isInitialized() {
        return true;
      }

      @java.lang.Override
      public Builder mergeFrom(
          com.google.protobuf.CodedInputStream input,
          com.google.protobuf.ExtensionRegistryLite extensionRegistry)
          throws java.io.IOException {
        if (extensionRegistry == null) {
          throw new java.lang.NullPointerException();
        }
        try {
          boolean done = false;
          while (!done) {
            int tag = input.readTag();
            switch (tag) {
              case 0:
                done = true;
                break;
              case 10: {
                PluginAdapter.Api.AnnouncementOuterClass.Announcement m =
                    input.readMessage(
                        PluginAdapter.Api.AnnouncementOuterClass.Announcement.parser(),
                        extensionRegistry);
                if (announcementsBuilder_ == null) {
                  ensureAnnouncementsIsMutable();
                  announcements_.add(m);
                } else {
                  announcementsBuilder_.addMessage(m);
                }
                break;
              } // case 10
              default: {
                if (!super.parseUnknownField(input, extensionRegistry, tag)) {
                  done = true; // was an endgroup tag
                }
                break;
              } // default:
            } // switch (tag)
          } // while (!done)
        } catch (com.google.protobuf.InvalidProtocolBufferException e) {
          throw e.unwrapIOException();
        } finally {
          onChanged();
        } // finally
        return this;
      }
      private int bitField0_;

      private java.util.List<PluginAdapter.Api.AnnouncementOuterClass.Announcement> announcements_ =
        java.util.Collections.emptyList();
      private void ensureAnnouncementsIsMutable() {
        if (!((bitField0_ & 0x00000001) != 0)) {
          announcements_ = new java.util.ArrayList<PluginAdapter.Api.AnnouncementOuterClass.Announcement>(announcements_);
          bitField0_ |= 0x00000001;
         }
      }

      private com.google.protobuf.RepeatedFieldBuilderV3<
          PluginAdapter.Api.AnnouncementOuterClass.Announcement, PluginAdapter.Api.AnnouncementOuterClass.Announcement.Builder, PluginAdapter.Api.AnnouncementOuterClass.AnnouncementOrBuilder> announcementsBuilder_;

      /**
       * <code>repeated .PluginAdapter.Api.Announcement announcements = 1;</code>
       */
      public java.util.List<PluginAdapter.Api.AnnouncementOuterClass.Announcement> getAnnouncementsList() {
        if (announcementsBuilder_ == null) {
          return java.util.Collections.unmodifiableList(announcements_);
        } else {
          return announcementsBuilder_.getMessageList();
        }
      }
      /**
       * <code>repeated .PluginAdapter.Api.Announcement announcements = 1;</code>
       */
      public int getAnnouncementsCount() {
        if (announcementsBuilder_ == null) {
          return announcements_.size();
        } else {
          return announcementsBuilder_.getCount();
        }
      }
      /**
       * <code>repeated .PluginAdapter.Api.Announcement announcements = 1;</code>
       */
      public PluginAdapter.Api.AnnouncementOuterClass.Announcement getAnnouncements(int index) {
        if (announcementsBuilder_ == null) {
          return announcements_.get(index);
        } else {
          return announcementsBuilder_.getMessage(index);
        }
      }
      /**
       * <code>repeated .PluginAdapter.Api.Announcement announcements = 1;</code>
       */
      public Builder setAnnouncements(
          int index, PluginAdapter.Api.AnnouncementOuterClass.Announcement value) {
        if (announcementsBuilder_ == null) {
          if (value == null) {
            throw new NullPointerException();
          }
          ensureAnnouncementsIsMutable();
          announcements_.set(index, value);
          onChanged();
        } else {
          announcementsBuilder_.setMessage(index, value);
        }
        return this;
      }
      /**
       * <code>repeated .PluginAdapter.Api.Announcement announcements = 1;</code>
       */
      public Builder setAnnouncements(
          int index, PluginAdapter.Api.AnnouncementOuterClass.Announcement.Builder builderForValue) {
        if (announcementsBuilder_ == null) {
          ensureAnnouncementsIsMutable();
          announcements_.set(index, builderForValue.build());
          onChanged();
        } else {
          announcementsBuilder_.setMessage(index, builderForValue.build());
        }
        return this;
      }
      /**
       * <code>repeated .PluginAdapter.Api.Announcement announcements = 1;</code>
       */
      public Builder addAnnouncements(PluginAdapter.Api.AnnouncementOuterClass.Announcement value) {
        if (announcementsBuilder_ == null) {
          if (value == null) {
            throw new NullPointerException();
          }
          ensureAnnouncementsIsMutable();
          announcements_.add(value);
          onChanged();
        } else {
          announcementsBuilder_.addMessage(value);
        }
        return this;
      }
      /**
       * <code>repeated .PluginAdapter.Api.Announcement announcements = 1;</code>
       */
      public Builder addAnnouncements(
          int index, PluginAdapter.Api.AnnouncementOuterClass.Announcement value) {
        if (announcementsBuilder_ == null) {
          if (value == null) {
            throw new NullPointerException();
          }
          ensureAnnouncementsIsMutable();
          announcements_.add(index, value);
          onChanged();
        } else {
          announcementsBuilder_.addMessage(index, value);
        }
        return this;
      }
      /**
       * <code>repeated .PluginAdapter.Api.Announcement announcements = 1;</code>
       */
      public Builder addAnnouncements(
          PluginAdapter.Api.AnnouncementOuterClass.Announcement.Builder builderForValue) {
        if (announcementsBuilder_ == null) {
          ensureAnnouncementsIsMutable();
          announcements_.add(builderForValue.build());
          onChanged();
        } else {
          announcementsBuilder_.addMessage(builderForValue.build());
        }
        return this;
      }
      /**
       * <code>repeated .PluginAdapter.Api.Announcement announcements = 1;</code>
       */
      public Builder addAnnouncements(
          int index, PluginAdapter.Api.AnnouncementOuterClass.Announcement.Builder builderForValue) {
        if (announcementsBuilder_ == null) {
          ensureAnnouncementsIsMutable();
          announcements_.add(index, builderForValue.build());
          onChanged();
        } else {
          announcementsBuilder_.addMessage(index, builderForValue.build());
        }
        return this;
      }
      /**
       * <code>repeated .PluginAdapter.Api.Announcement announcements = 1;</code>
       */
      public Builder addAllAnnouncements(
          java.lang.Iterable<? extends PluginAdapter.Api.AnnouncementOuterClass.Announcement> values) {
        if (announcementsBuilder_ == null) {
          ensureAnnouncementsIsMutable();
          com.google.protobuf.AbstractMessageLite.Builder.addAll(
              values, announcements_);
          onChanged();
        } else {
          announcementsBuilder_.addAllMessages(values);
        }
        return this;
      }
      /**
       * <code>repeated .PluginAdapter.Api.Announcement announcements = 1;</code>
       */
      public Builder clearAnnouncements() {
        if (announcementsBuilder_ == null) {
          announcements_ = java.util.Collections.emptyList();
          bitField0_ = (bitField0_ & ~0x00000001);
          onChanged();
        } else {
          announcementsBuilder_.clear();
        }
        return this;
      }
      /**
       * <code>repeated .PluginAdapter.Api.Announcement announcements = 1;</code>
       */
      public Builder removeAnnouncements(int index) {
        if (announcementsBuilder_ == null) {
          ensureAnnouncementsIsMutable();
          announcements_.remove(index);
          onChanged();
        } else {
          announcementsBuilder_.remove(index);
        }
        return this;
      }
      /**
       * <code>repeated .PluginAdapter.Api.Announcement announcements = 1;</code>
       */
      public PluginAdapter.Api.AnnouncementOuterClass.Announcement.Builder getAnnouncementsBuilder(
          int index) {
        return getAnnouncementsFieldBuilder().getBuilder(index);
      }
      /**
       * <code>repeated .PluginAdapter.Api.Announcement announcements = 1;</code>
       */
      public PluginAdapter.Api.AnnouncementOuterClass.AnnouncementOrBuilder getAnnouncementsOrBuilder(
          int index) {
        if (announcementsBuilder_ == null) {
          return announcements_.get(index);  } else {
          return announcementsBuilder_.getMessageOrBuilder(index);
        }
      }
      /**
       * <code>repeated .PluginAdapter.Api.Announcement announcements = 1;</code>
       */
      public java.util.List<? extends PluginAdapter.Api.AnnouncementOuterClass.AnnouncementOrBuilder> 
           getAnnouncementsOrBuilderList() {
        if (announcementsBuilder_ != null) {
          return announcementsBuilder_.getMessageOrBuilderList();
        } else {
          return java.util.Collections.unmodifiableList(announcements_);
        }
      }
      /**
       * <code>repeated .PluginAdapter.Api.Announcement announcements = 1;</code>
       */
      public PluginAdapter.Api.AnnouncementOuterClass.Announcement.Builder addAnnouncementsBuilder() {
        return getAnnouncementsFieldBuilder().addBuilder(
            PluginAdapter.Api.AnnouncementOuterClass.Announcement.getDefaultInstance());
      }
      /**
       * <code>repeated .PluginAdapter.Api.Announcement announcements = 1;</code>
       */
      public PluginAdapter.Api.AnnouncementOuterClass.Announcement.Builder addAnnouncementsBuilder(
          int index) {
        return getAnnouncementsFieldBuilder().addBuilder(
            index, PluginAdapter.Api.AnnouncementOuterClass.Announcement.getDefaultInstance());
      }
      /**
       * <code>repeated .PluginAdapter.Api.Announcement announcements = 1;</code>
       */
      public java.util.List<PluginAdapter.Api.AnnouncementOuterClass.Announcement.Builder> 
           getAnnouncementsBuilderList() {
        return getAnnouncementsFieldBuilder().getBuilderList();
      }
      private com.google.protobuf.RepeatedFieldBuilderV3<
          PluginAdapter.Api.AnnouncementOuterClass.Announcement, PluginAdapter.Api.AnnouncementOuterClass.Announcement.Builder, PluginAdapter.Api.AnnouncementOuterClass.AnnouncementOrBuilder> 
          getAnnouncementsFieldBuilder() {
        if (announcementsBuilder_ == null) {
          announcementsBuilder_ = new com.google.protobuf.RepeatedFieldBuilderV3<
              PluginAdapter.Api.AnnouncementOuterClass.Announcement, PluginAdapter.Api.AnnouncementOuterClass.Announcement.Builder, PluginAdapter.Api.AnnouncementOuterClass.AnnouncementOrBuilder>(
                  announcements_,
                  ((bitField0_ & 0x00000001) != 0),
                  getParentForChildren(),
                  isClean());
          announcements_ = null;
        }
        return announcementsBuilder_;
      }
      @java.lang.Override
      public final Builder setUnknownFields(
          final com.google.protobuf.UnknownFieldSet unknownFields) {
        return super.setUnknownFields(unknownFields);
      }

      @java.lang.Override
      public final Builder mergeUnknownFields(
          final com.google.protobuf.UnknownFieldSet unknownFields) {
        return super.mergeUnknownFields(unknownFields);
      }


      // @@protoc_insertion_point(builder_scope:PluginAdapter.Api.Announcements)
    }

    // @@protoc_insertion_point(class_scope:PluginAdapter.Api.Announcements)
    private static final PluginAdapter.Api.AnnouncementsOuterClass.Announcements DEFAULT_INSTANCE;
    static {
      DEFAULT_INSTANCE = new PluginAdapter.Api.AnnouncementsOuterClass.Announcements();
    }

    public static PluginAdapter.Api.AnnouncementsOuterClass.Announcements getDefaultInstance() {
      return DEFAULT_INSTANCE;
    }

    private static final com.google.protobuf.Parser<Announcements>
        PARSER = new com.google.protobuf.AbstractParser<Announcements>() {
      @java.lang.Override
      public Announcements parsePartialFrom(
          com.google.protobuf.CodedInputStream input,
          com.google.protobuf.ExtensionRegistryLite extensionRegistry)
          throws com.google.protobuf.InvalidProtocolBufferException {
        Builder builder = newBuilder();
        try {
          builder.mergeFrom(input, extensionRegistry);
        } catch (com.google.protobuf.InvalidProtocolBufferException e) {
          throw e.setUnfinishedMessage(builder.buildPartial());
        } catch (com.google.protobuf.UninitializedMessageException e) {
          throw e.asInvalidProtocolBufferException().setUnfinishedMessage(builder.buildPartial());
        } catch (java.io.IOException e) {
          throw new com.google.protobuf.InvalidProtocolBufferException(e)
              .setUnfinishedMessage(builder.buildPartial());
        }
        return builder.buildPartial();
      }
    };

    public static com.google.protobuf.Parser<Announcements> parser() {
      return PARSER;
    }

    @java.lang.Override
    public com.google.protobuf.Parser<Announcements> getParserForType() {
      return PARSER;
    }

    @java.lang.Override
    public PluginAdapter.Api.AnnouncementsOuterClass.Announcements getDefaultInstanceForType() {
      return DEFAULT_INSTANCE;
    }

  }

  private static final com.google.protobuf.Descriptors.Descriptor
    internal_static_PluginAdapter_Api_Announcements_descriptor;
  private static final 
    com.google.protobuf.GeneratedMessageV3.FieldAccessorTable
      internal_static_PluginAdapter_Api_Announcements_fieldAccessorTable;

  public static com.google.protobuf.Descriptors.FileDescriptor
      getDescriptor() {
    return descriptor;
  }
  private static  com.google.protobuf.Descriptors.FileDescriptor
      descriptor;
  static {
    java.lang.String[] descriptorData = {
      "\n\023announcements.proto\022\021PluginAdapter.Api" +
      "\032\022announcement.proto\"G\n\rAnnouncements\0226\n" +
      "\rannouncements\030\001 \003(\0132\037.PluginAdapter.Api" +
      ".Announcementb\006proto3"
    };
    descriptor = com.google.protobuf.Descriptors.FileDescriptor
      .internalBuildGeneratedFileFrom(descriptorData,
        new com.google.protobuf.Descriptors.FileDescriptor[] {
          PluginAdapter.Api.AnnouncementOuterClass.getDescriptor(),
        });
    internal_static_PluginAdapter_Api_Announcements_descriptor =
      getDescriptor().getMessageTypes().get(0);
    internal_static_PluginAdapter_Api_Announcements_fieldAccessorTable = new
      com.google.protobuf.GeneratedMessageV3.FieldAccessorTable(
        internal_static_PluginAdapter_Api_Announcements_descriptor,
        new java.lang.String[] { "Announcements", });
    PluginAdapter.Api.AnnouncementOuterClass.getDescriptor();
  }

  // @@protoc_insertion_point(outer_class_scope)
}