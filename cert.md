# Cert

```c
static int load_tls_type(struct lwm2m_ctx *client_ctx, uint16_t res_id,
			       enum tls_credential_type type)
{
	int ret = 0;
	void *cred = NULL;
	uint16_t cred_len;
	uint16_t max_len;

	ret = lwm2m_get_res_buf(&LWM2M_OBJ(0, client_ctx->sec_obj_inst, res_id), &cred, &max_len,
				&cred_len, NULL);
	if (ret < 0) {
		LOG_ERR("Unable to get resource data for %d/%d/%d", 0,  client_ctx->sec_obj_inst,
			res_id);
		return ret;
	}

	if (cred_len == 0) {
		LOG_ERR("Credential data is empty");
		return -EINVAL;
	}

	/* LwM2M registry stores strings without NULL-terminator, so we need to ensure that
	 * string based PEM credentials are terminated properly.
	 */
	if (is_pem(cred, cred_len)) {
		if (cred_len >= max_len) {
			LOG_ERR("No space for string terminator, cannot handle PEM");
			return -EINVAL;
		}
		((uint8_t *) cred)[cred_len] = 0;
		cred_len += 1;
	}

	ret = tls_credential_add(client_ctx->tls_tag, type, cred, cred_len);
	if (ret < 0) {
		LOG_ERR("Error setting cred tag %d type %d: Error %d", client_ctx->tls_tag, type,
			ret);
	}

	return ret;
}
```



```c
static int lwm2m_load_x509_credentials(struct lwm2m_ctx *ctx)
{
	int ret;

	delete_tls_credentials(ctx->tls_tag);

	ret = load_tls_type(ctx, 3, TLS_CREDENTIAL_SERVER_CERTIFICATE);
	if (ret < 0) {
		return ret;
	}
	ret = load_tls_type(ctx, 5, TLS_CREDENTIAL_PRIVATE_KEY);
	if (ret < 0) {
		return ret;
	}

	ret = load_tls_type(ctx, 4, TLS_CREDENTIAL_CA_CERTIFICATE);
	if (ret < 0) {
		return ret;
	}
	return ret;
}
```



```c
static int lwm2m_load_tls_credentials(struct lwm2m_ctx *ctx)
{
	switch (lwm2m_security_mode(ctx)) {
	case LWM2M_SECURITY_NOSEC:
		if (ctx->use_dtls) {
			return -EINVAL;
		}
		return 0;
	case LWM2M_SECURITY_PSK:
		return lwm2m_load_psk_credentials(ctx);
	case LWM2M_SECURITY_CERT:
		return lwm2m_load_x509_credentials(ctx);
	default:
		return -EOPNOTSUPP;
	}
}
```

